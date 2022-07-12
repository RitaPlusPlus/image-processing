#include "gaussian_filter.h"

// Gaussian standard deviation
double GaussianFilter::getGaussianKernelForPoint(const int row, const int col, const int radius) const
{
    return (1.0 / (2 * M_PI * pow(sigma, 2)) * exp ( - (pow(row - radius, 2) + pow(col - radius, 2)) / (2 * pow(sigma, 2))));
}

void GaussianFilter::initKernel()
{
    // Gaussian kernel
    if(radius > 0) {
        size = 2 * radius + (radius % 2);
        kernel = new double* [size];

        for (int row = 0; row < size; row++)
        {
            kernel[row] = new double [size];
            for (int col = 0; col < size; col++)
            {
                kernel[row][col] = getGaussianKernelForPoint(row, col, radius);
            }
        }
    }
}


void GaussianFilter::init(const QPoint &center, const QImage &image, QRgb** matrix)
{
    QSize image_size = image.size();
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            matrix[row][col] = image.pixel(getCoordinate(QPoint(row, col) + center, image_size));
        }
    }
}


QRgb GaussianFilter::transform(QRgb **matrix)
{
    // applies the kernel
    double red = 0.0, blue = 0.0, green = 0.0;
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            red += qRed(matrix[row][col]) * kernel[row][col];
            blue += qBlue(matrix[row][col]) * kernel[row][col];
            green += qGreen(matrix[row][col]) * kernel[row][col];
        }
    }
    return qRgb(red, green, blue);
}


QPoint GaussianFilter::getCoordinate(const QPoint &point, const QSize &image_size)
{
    // Get coordinate depending on the image size and the radius
    QPoint result(point);

    int xpos = result.x() - radius, ypos = result.y() - radius;
    result.setX(xpos < 0 ? 0 : (xpos >= image_size.width() ? image_size.width() - 1 : xpos));
    result.setY(ypos < 0 ? 0 : (ypos >= image_size.height() ? image_size.height() - 1 : ypos));

    return result;
}


void GaussianFilter::normalize()
{
    // normalize with the kernel sum
    double sum = getSum();
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            kernel[row][col] /= sum;
        }
    }
}

GaussianFilter::GaussianFilter(int radius, double sigma) : radius (radius), sigma (sigma)
{
    initKernel();
    normalize();
}

GaussianFilter::~GaussianFilter()
{
    free();
}

void GaussianFilter::free()
{
    for (int row = 0; row < size; row++)
    {
        delete[] kernel[row];
    }
    delete[] kernel;
}

double GaussianFilter::getSum() const
{
    // Gets the sum of the kernel elements
    double result = 0.0;
    for (int row = 0; row < size; row++)
    {
        for (int col = 0; col < size; col++)
        {
            result += kernel[row][col];
        }
    }

    return result;
}

void GaussianFilter::apply(QImage &input)
{
    QRgb **temp = new QRgb* [size];
    for (int row = 0; row < size; row++)
    {
        temp[row] = new QRgb [size];
    }

    for (int row = 0; row < input.width(); row++)
    {
        for (int col = 0; col < input.height(); col++)
        {
            init(QPoint(row, col), input, temp);
            input.setPixel(QPoint(row,col), transform(temp));
        }
    }

    // erase the temp data
    for (int row = 0; row < size; row++)
    {
        delete[] temp[row];
    }
    delete[] temp;
}
