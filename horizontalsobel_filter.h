#ifndef HORIZONTALSOBELFILTER_H
#define HORIZONTALSOBELFILTER_H

#include <QImage>

class horizontalSobelFilter
{
public:
    horizontalSobelFilter();

    QImage horizontalSobelGradientFilter(const  uchar* imageData, const int width, const int height, const QImage::Format format);
    QImage applyFilter(const uchar *image, const int width, const int height, const QImage::Format format, const int kernelRadius, const int kernel[], const float kernelParameter,
                                              QColor (*convolution)(const uchar *,const int, const int,
                                                                   const int , const int[], const float ,const int ,
                                                                   const int ,const int ));

    static QColor applyConvolution(const uchar *image,const int width, const int height,
                                                   const int kernelRadius, const int kernel[], const float kernelParameter,const int kernelWidth,
                                                   const int x,const int y);
};

#endif // HORIZONTALSOBELFILTER_H
