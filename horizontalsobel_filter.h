#ifndef HORIZONTALSOBELFILTER_H
#define HORIZONTALSOBELFILTER_H

#include <QImage>

class horizontalSobelFilter
{
public:
    // Horizontal Sobel Filter
    horizontalSobelFilter();


    // Horizontal Sobel Filter kernel
    QImage horizontalSobelGradientFilter(const  unsigned char* imageData, const int width, const int height, const QImage::Format f);


    // apply Horizontal Sobel Filter
    QImage applyHSFilter(const unsigned char *image, const int width, const int height, const QImage::Format format, const int kernelRadius, const int kernel[], const double kernelParameter,
                                              QColor (*convolution)(const unsigned char *,const int, const int,
                                                                   const int , const int[], const double ,const int ,
                                                                   const int ,const int ));

    /* apply convolution function */
    static QColor applyConv(const unsigned char *image,const int width, const int height,
                                                   const int kernelRadius, const int kernel[], const double kernelParameter,const int kernelWidth,
                                                   const int x,const int y);
};

#endif // HORIZONTALSOBELFILTER_H
