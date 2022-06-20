#ifndef GRADIENT_FILTER_H
#define GRADIENT_FILTER_H

#include <QImage>

class GradientFilter
{
public:
    GradientFilter();
    QImage gradientFilter(const  uchar* imageData,const int width, const int height,const QImage::Format format);


    QImage convertToGrayScale(const  uchar* imageData,const int width,const int height,const QImage::Format format);

};

#endif // GRADIENT_FILTER_H
