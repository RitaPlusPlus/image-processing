#ifndef MEAN_FILTER_H
#define MEAN_FILTER_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QDialog>
#include <QFileDialog>
#include <QImage>
#include <QRgb>
#include <QList>

#include <thread>
#include <functional>
#include <string>

using namespace std;

class MeanFilter
{
public:
    MeanFilter();

   // MeanFilter(QImage *image = nullptr);

    QImage meanBlur(const  uchar* imageData, const int width, const int height, const QImage::Format format);

    QImage applyFilter(const uchar *image, const int width, const int height, const QImage::Format format, const int kernelRadius, const int kernel[], const float kernelParameter,
                                                  QColor (*convolution)(const uchar *,const int, const int,
                                                                       const int , const int[], const float ,const int ,
                                                                       const int ,const int ));
    static QColor applyConvolution(const uchar *image,
                                        const int width,
                                        const int height,
                                        const int kernelRadius,
                                        const int kernel[],
                                        const float kernelParameter,
                                        const int kernelWidth,
                                        const int x,
                                        const int y);



};

#endif // MEAN_FILTER_H
