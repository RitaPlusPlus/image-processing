#include "gaussian_filter.h"

// Gaussian standard deviation
double GaussianFilter::getGaussianKernelForPoint(const int row, const int col, const int radius) const
{
    return (1.0 / (2 * M_PI * pow(sigma, 2)) * exp ( - (pow(row - radius, 2) + pow(col - radius, 2)) / (2 * pow(sigma, 2))));
}

void GaussianFilter::initKernel()
{
//    // Gauusian
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


    // Laplacian
//    if(radius > 0) {
//        size = 3;
//        kernel = new double* [size];

//        for (int row = 0; row < size; row++)
//        {
//            kernel[row] = new double [size];
//        }
//        kernel[0][0] = 0;
//        kernel[0][1] = -1;
//        kernel[0][2] = 0;
//        kernel[1][0] = -1;
//        kernel[1][1] = 4;
//        kernel[1][2] = -1;
//        kernel[2][0] = 0;
//        kernel[2][1] = -1;
//        kernel[2][2] = 0;
//    }
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
    QPoint result(point);

    int xpos = result.x() - radius, ypos = result.y() - radius;
    result.setX(xpos < 0 ? 0 : (xpos >= image_size.width() ? image_size.width() - 1 : xpos));
    result.setY(ypos < 0 ? 0 : (ypos >= image_size.height() ? image_size.height() - 1 : ypos));

    return result;
}


void GaussianFilter::normalize()
{
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

    for (int row = 0; row < size; row++)
    {
        delete[] temp[row];
    }
    delete[] temp;
}

//Filter::Filter(const Filter &original):
//            radius_(original.radius_),
//            diviation_(original.diviation_)
//{
//    size_ = 2 * radius_ + 1;
//    matrix_ = new double* [size_];

//    for (int i = 0; i < size_; i++)
//        matrix_[i] = new double [size_];
//    for (int i = 0; i < size_; i++)
//        for (int j = 0; j < size_; j++)
//            matrix_[i][j] = original.matrix_[i][j];
//}

//const Filter& Filter::operator = (const Filter &blur)
//{
//    if (this != &blur)
//    {
//        for (int i = 0; i < size_; i ++)
//            delete[] matrix_[i];
//        delete[] matrix_;

//        radius_ = blur.radius_;
//        diviation_ = blur.diviation_;
//        size_ = blur.size_;
//        matrix_ = new double* [size_];

//        for (int i = 0; i < size_; i++)
//            matrix_[i] = new double [size_];
//        for (int i = 0; i < size_; i++)
//            for (int j = 0; j < size_; j++)
//                matrix_[i][j] = blur.matrix_[i][j];
//    }
//    return *this;
//}


//QTextStream &operator << (QTextStream &stream, const Filter &blur) {
//    stream.setRealNumberPrecision(6);
//    for (int i = 0; i < blur.size_; i++) {
//        for (int j = 0; j < blur.size_; j++)
//            stream << blur.matrix_[i][j] << " ";
//        stream << Qt::endl;
//    }
//    return stream;
//}
