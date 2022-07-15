#ifndef CHANGE_IMG_COLOUR_H
#define CHANGE_IMG_COLOUR_H

#include <QImage>
// https://doc.qt.io/qt-6/qimage.html#bits
// https://www.dynamsoft.com/blog/insights/image-processing/image-processing-101-color-space-conversion/
class BlckWhtclr
{
    public:
        //! Black and White colour
        /*!
            Black and White colour
        */
        BlckWhtclr();

        //! set Black and White colour
        /*!
            change the colour of the uploaded image to be Black and White
        */
        QImage setBlckWht(const unsigned char* img, const int width, const int height, const QImage::Format f);
};

#endif // CHANGE_IMG_COLOUR_H
