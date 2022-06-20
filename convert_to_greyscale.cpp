#include "convert_to_greyscale.h"

toGreyScale::toGreyScale()
{

}

QImage toGreyScale::convert(const  uchar* imageData,const int width,const int height,const QImage::Format format)
{
    QImage* grayScaleImage = new QImage(width,height,format);
    uchar* grayScaleImageData = grayScaleImage->bits();
    for(int i= 0;i<height * width * 4; i+=4 )
    {
        float greyScaleValue = 0.299f * imageData[i] + 0.587f * imageData[i+1] + 0.114f *imageData[i+2];
        //Red
        grayScaleImageData[i] = greyScaleValue;
        //Green
        grayScaleImageData[i+1] = greyScaleValue;
        //Blue
        grayScaleImageData[i+2] = greyScaleValue;
        //Alpha
        grayScaleImageData[i+3] = imageData[i +3];
    }
    return *grayScaleImage;
}
