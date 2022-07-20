#ifndef CHANGE_IMG_COLOUR_H
#define CHANGE_IMG_COLOUR_H

#include <QImage>
// https://doc.qt.io/qt-6/qimage.html#bits
// https://www.dynamsoft.com/blog/insights/image-processing/image-processing-101-color-space-conversion/
class GrayscaleImg
{
    public:
        //! Grayscale image
        /*!
            Grayscale image
        */
        GrayscaleImg();

        //! set to Grayscale
        /*!
            change the colour of the uploaded image to different shades of gray
        */
        QImage setGrscl(const unsigned char* img, const int width, const int height, const QImage::Format f);
};

#endif // CHANGE_IMG_COLOUR_H
