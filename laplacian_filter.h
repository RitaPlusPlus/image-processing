#ifndef LAPLACIANFILTER_H
#define LAPLACIANFILTER_H

#include <QImage>

class LaplacianFilter
{
public:
    LaplacianFilter();

    //! Apply Gaussian Laplacian
    /*!
        Apply Gaussian Laplacian with specific Gaussian kernel
        \param image  image itself
        \param scale  scale for the edge detection
    */
    QImage applyLaplacianGaussian(const QImage &image, double scale);

    //! Apply just laplacian (NOT USED CURRENTLY)
    /*!
        Apply Laplacian with different kernel
        \param image  image itself
        \param scale  scale for the edge detection
        \param mode   mode for the calculation
    */
    QImage applyLaplacian(const QImage &image, double scale, int mode);
};

#endif // LAPLACIANFILTER_H
