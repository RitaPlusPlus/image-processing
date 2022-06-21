#ifndef MEAN_FILTER_H
#define MEAN_FILTER_H

#include <QImage>

using namespace std;

class MeanFilter
{
public:
    MeanFilter();

    QImage applyMeanBlurFilter(const unsigned char* image, const int width, const int height, const QImage::Format format);
    QImage applyMean(const unsigned char *image, const int width, const int height, const QImage::Format format,
                           const int kernelRadius, const int kernel[], const double kernelParameter,
                           QColor (*conv)(const unsigned char *, const int, const int, const int,
                                                 const int[], const double, const int, const int, const int)
                           );
    /* convolution (conv) */
    static QColor conv( const unsigned char *image,
                        const int width,
                        const int height,
                        const int kernelRadius,
                        const int kernel[],
                        const double kernelParameter,
                        const int kernelWidth,
                        const int x,
                        const int y
                      );
};

#endif // MEAN_FILTER_H
