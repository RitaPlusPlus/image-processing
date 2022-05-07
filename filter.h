#ifndef FILTER_H
#define FILTER_H

#include <QTextStream>
#include <QImage>
#include <qmath.h>

class Filter {
private:
    //! pixels on the screen blend into each other
    /*!
        pixels on the screen blend into each other
    */
    int radius;
    int size;
    double sigma;
    double **kernel;

private:
    double getKernelForPoint(const int row, const int col, const int radius) const;
    void initKernel();
    void init(const QPoint &center, const QImage &image, QRgb **matrix);
    QRgb transform(QRgb** matrix);
    QPoint getCoordinate(const QPoint &point, const QSize &image_size);
    void normalize();
    double getSum() const;

    //! Access element at index
    /*!
        Access element at index
        \param i    index
        \return     value
    */
    void free();

public:
    Filter(int radius = 1, double sigma = 1.0);
//    Filter(const Filter &original);
    ~Filter();

    QImage apply(const QImage input);

//    const Filter &operator = (const Filter &blur);
//    friend QTextStream &operator << (QTextStream &stream, const Filter &blur);
};

#endif // FILTER_H
