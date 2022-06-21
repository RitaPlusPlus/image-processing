#ifndef CHANGE_IMG_COLOUR_H
#define CHANGE_IMG_COLOUR_H

#include <QImage>

class BlckWhtclr
{
public:
    BlckWhtclr();
    QImage setBlckWht(const unsigned char* img,const int width,const int height, const QImage::Format f);
};

#endif // CHANGE_IMG_COLOUR_H
