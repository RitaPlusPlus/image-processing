#ifndef GAUSSIAN_FILTER_H
#define GAUSSIAN_FILTER_H

#include <QTextStream>
#include <QImage>
#include <qmath.h>

class GaussianFilter {
private:
    //! radius of the kernel
    /*!
        radius of the kernel
    */
    int radius;

    //! size of the kernel
    /*!
        size of the kernel
    */
    int size;

    //! sigma for the kernel
    /*!
        sigma for the kernel
    */
    double sigma;

    //! kernel
    /*!
        kernel
    */
    double **kernel;

private:
    //! calculates formula for the kernel
    /*!
        calculates formula for the kernel
        \param row  current row
        \param col  current col
        \param radius  radius from input
    */
    double getGaussianKernelForPoint(const int row, const int col, const int radius) const;

    //! Initialise the kernel
    /*!
        Initialise the kernel
     */
    void initKernel();

    //! Init the object
    /*!
        Init the object
    */
    void init(const QPoint &center, const QImage &image, QRgb **matrix);

    //! Apply the kernel
    /*!
        Apply the kernel
        \param matrix  the image itself
    */
    QRgb transform(QRgb** matrix);

    //! Get coordinate
    /*!
        Get coordinate
        \param point  point itself
        \param image_size  the size of the image
    */
    QPoint getCoordinate(const QPoint &point, const QSize &image_size);

    //! Normalize with the sum of the kernel values
    /*!
        Normalize with the sum of the kernel values
    */
    void normalize();

    //! Get sum of the kernel elements
    /*!
        Get sum of the kernel elements
    */
    double getSum() const;

    //! Access element at index
    /*!
        Access element at index
        \param i    index
        \return     value
    */
    void free();

public:
    GaussianFilter(int radius = 1, double sigma = 1.0);
//    Filter(const Filter &original);
    ~GaussianFilter();

    void apply(QImage &input);

//    const Filter &operator = (const Filter &blur);
//    friend QTextStream &operator << (QTextStream &stream, const Filter &blur);
};

#endif // GAUSSIAN_FILTER_H
