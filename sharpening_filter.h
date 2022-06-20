#ifndef SHARPENING_FILTER_H
#define SHARPENING_FILTER_H

#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QTextStream>
#include <QString>

const int INTENS_MIN = 0;
const int INTENS_MAX = 255;
const int KERN_SIZE = 3;
const double KERN_ELEM = 1.0 / (KERN_SIZE * KERN_SIZE);



class Sharpening
{
public:
    Sharpening();
    void filter(const QImage &in_image, QImage &out_image);//double kernel[][KERN_SIZE]);
    void applyS(QImage &in_image);
    QRgb convolute(const QList<int> &kernel, const QImage &image, int x, int y);

    private:
        int x;
        int y;
};

#endif // SHARPENING_FILTER_H
