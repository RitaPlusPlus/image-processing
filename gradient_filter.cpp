#include "gradient_filter.h"
#include <cmath>

using namespace std;

GradientFilter::GradientFilter()
{
}/* GradientFilter */


QImage GradientFilter::applyGradientFilter(const unsigned char* image, const int width, const int height, const QImage::Format f)
{
    //https://homepages.inf.ed.ac.uk/rbf/HIPR2/sobel.htm
    //https://www.slideshare.net/PreethaHelen/sharpening-spatial-filters-67662870
    //https://medium.com/jun94-devpblog/cv-3-gradient-and-laplacian-filter-difference-of-gaussians-dog-7c22e4a9d6cc

    const int n = 2; /* from Sobel is this 2, but we can also use 1 instead that comes from Prewitt */
    //Sobel's Method
    const int x_kernel[9] = {-1, 0, 1, -n, 0, n, -1, 0, 1};
    const int y_kernel[9] = {-1, -n, -1, 0, 0, 0, 1, n, 1};

    const int radius_kernel = 1;
    const int width_kernel = 3;


    QImage* new_image = new QImage(width, height, f);
    unsigned char* filtered_image = new_image->bits();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            double x_gradient[3] = {0.0, 0.0, 0.0};
            double y_gradient[3] = {0.0, 0.0, 0.0};

            for (int k = -radius_kernel; k <= radius_kernel; k++)
            {
                int x_k = k + radius_kernel;
                int x = MAX( MIN(i + k, width - 1),0);

                for (int l = -radius_kernel; l <= radius_kernel; l++)
                {
                    int y_k = l + radius_kernel;
                    int y = MAX( MIN( j + l, height - 1), 0);

                    int index = 4 * x + y * width * 4;
                    int red = image[index];
                    int green = image[index + 1];
                    int blue = image[index + 2];

                    double h = x_kernel[x_k + y_k * width_kernel];
                    double hY = y_kernel[x_k + y_k * width_kernel];

                    x_gradient[0] += (red * h);
                    x_gradient[1] += (green * h);
                    x_gradient[2] += (blue * h);

                    y_gradient[0] += (red * hY);
                    y_gradient[1] += (green * hY);
                    y_gradient[2] += (blue * hY);

                }
            }
            x_gradient[0] /= (n + 2);
            x_gradient[1] /= (n + 2);
            x_gradient[2] /= (n + 2);

            y_gradient[0] /= (n + 2);
            y_gradient[1] /= (n + 2);
            y_gradient[2] /= (n + 2);

            int index = 4 * i + j * width * 4;
            /* red */
            filtered_image[index] = sqrt(pow(x_gradient[0], 2) + pow(y_gradient[0], 2));
            /* green */
            filtered_image[index + 1] = sqrt(pow(x_gradient[1], 2) + pow(y_gradient[1], 2));
            /* blue */
            filtered_image[index + 2] = sqrt(pow(x_gradient[2], 2) + pow(y_gradient[2], 2));
            /* alpha */
            filtered_image[index + 3] = 255.0;
        }
    }
    return (*new_image);
}/* applyGradientFilter */

