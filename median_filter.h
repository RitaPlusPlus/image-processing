#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include <QImage>

class MedianFilter
{
public:
    MedianFilter();
    QImage applyMedianFilter(const uchar* imageData, const int width, const int height, QImage::Format format);
};

#endif // MEDIANFILTER_H
