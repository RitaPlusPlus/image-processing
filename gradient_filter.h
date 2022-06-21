#ifndef GRADIENT_FILTER_H
#define GRADIENT_FILTER_H

#include <QImage>

#define MIN(x, y) (x < y ? x : y)
#define MAX(x, y) (x > y ? x : y)

class GradientFilter
{
public:
    GradientFilter();
    QImage applyGradientFilter(const unsigned char* image, const int width, const int height, const QImage::Format f);
};

#endif // GRADIENT_FILTER_H
