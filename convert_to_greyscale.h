#ifndef CONVERT_TO_GREYSCALE_H
#define CONVERT_TO_GREYSCALE_H

#include <QImage>

class toGreyScale
{
public:
    toGreyScale();
    QImage convert(const  uchar* imageData,const int width,const int height,const QImage::Format format);
};

#endif // CONVERT_TO_GREYSCALE_H
