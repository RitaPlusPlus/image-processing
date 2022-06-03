#ifndef LAPLACIANFILTER_H
#define LAPLACIANFILTER_H

#include <QImage>

class LaplacianFilter
{
public:
    LaplacianFilter();

    QImage applyLaplacianGaussian(const QImage &image,double scale);

    QImage applyLaplacian(const QImage &image,double scale,int mode);
};

#endif // LAPLACIANFILTER_H
