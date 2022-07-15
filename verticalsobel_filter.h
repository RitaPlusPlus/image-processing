#ifndef VERTICALSOBELFILTER_H
#define VERTICALSOBELFILTER_H

#include <QImage>

class verticalSobelFilter
{
public:
    // Vertical Sobel Filter
    verticalSobelFilter();


    // Vertical Sobel Filter kernel
    QImage verticalSobelGradientFilter(const  unsigned char* imageData, const int width, const int height, const QImage::Format f);


    // apply Vertical Sobel Filter
    QImage applyVSFilter(const unsigned char *image, const int width, const int height, const QImage::Format format, const int kernelRadius, const int kernel[], const double kernelParameter,
                                              QColor (*convolution)(const unsigned char *,const int, const int,
                                                                   const int , const int[], const double ,const int ,
                                                                   const int ,const int ));

    /* apply convolution function */
    static QColor applyConv(const unsigned char *image,const int width, const int height,
                                                   const int kernelRadius, const int kernel[], const double kernelParameter,const int kernelWidth,
                                                   const int x,const int y);
};

#endif // VERTICALSOBELFILTER_H
