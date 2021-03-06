#include "mean_filter.h"

#include <cstdlib> //abs() - returns the absolute value of an integer number.

using namespace std;

MeanFilter::MeanFilter()
{
}/* MeanFilter */

QImage MeanFilter::applyMeanBlurFilter(const unsigned char* image, const int width, const int height, const QImage::Format f)
{
    const int kernel[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1};

    return applyMean(image, width, height, f, 1, kernel, 9.0, &MeanFilter::conv);
} /* applyMeanBlurFilter */

QImage MeanFilter::applyMean( const unsigned char *image,
                              const int width,
                              const int height,
                              const QImage::Format f,
                              const int radius_kernel,
                              const int kernel[],
                              const double parameter_kernel,
                              QColor (*convolution)(  const unsigned char *image,
                                               const int width,
                                               const int height,
                                               const int radius_kernel,
                                               const int kernel[],
                                               const double parameter_kernel,
                                               const int width_kernel,
                                               const int x,
                                               const int y
                                           )
                             )
{
    const int width_kernel = 2 * radius_kernel + 1;  

    QImage* new_image = new QImage(width, height, f);
    unsigned char* filtered_image = new_image->bits();


    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            QColor color = convolution(image, width, height, radius_kernel, kernel, parameter_kernel, width_kernel, x, y);

            int index = 4 * x + y * width * 4 ;
            filtered_image[index] = color.red();
            filtered_image[index + 1] = color.green();
            filtered_image[index + 2] = color.blue();
            filtered_image[index + 3] = color.alpha();
        }
    }
    return (*new_image);
}/* applyMean */

/* convolution function on 3 Channel RGB image */
QColor MeanFilter::conv( const unsigned char *image,
                         const int width,
                         const int height,
                         const int radius_kernel,
                         const int kernel[],
                         const double parameter_kernel,
                         const int width_kernel,
                         const int x,
                         const int y
                       )
{
    int r = 0;
    int g = 0;
    int b = 0;

    //https://stackoverflow.com/questions/41756502/what-does-kernel-radius-mean
    /*
     * The kernel radius is the limit on absolute(x) and absolute(y) of the support of the convolution kernel.
     */
    for (int kx = - radius_kernel; kx <= radius_kernel; kx++)
    {
        int i_kernel = kx + radius_kernel;

        /* index i of the neighboor pixel */
        int i = fmax( fmin(x + kx, width - 1), 0);
        for (int ky = -radius_kernel; ky <= radius_kernel; ky++)
        {
            int j_kernel = ky + radius_kernel;
            /* index j of the neighboor pixel */
            int j = fmax( fmin(y + ky, height - 1), 0);
            QColor imageColor =  QColor(image[ 4 * i + j * width * 4],
                                        image[ 4 * i + j * width * 4 + 1],
                                        image[ 4 * i + j * width * 4 + 2],
                                        image[ 4 * i + j * width * 4 + 3]
                                        );

            double h = kernel[ i_kernel + j_kernel * width_kernel] / parameter_kernel;
            r = fminf(r + imageColor.red() * h, 255.0f);
            g = fminf(g + imageColor.green() * h, 255.0f);
            b = fminf(b + imageColor.blue() * h, 255.0f);

        }
    }
    return QColor(abs(r), abs(g), abs(b));
}/* conv */


