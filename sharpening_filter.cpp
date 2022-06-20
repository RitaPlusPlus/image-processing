#include "sharpening_filter.h"
#include <QtGui>

Sharpening::Sharpening()
{

}
/*
void Sharpening::filter(const QImage &in_image, QImage &out_image)//,double kernel[][KERN_SIZE])
{
    double kernel[][KERN_SIZE] = {
        {KERN_ELEM, KERN_ELEM, KERN_ELEM},
        {KERN_ELEM, KERN_ELEM, KERN_ELEM},
        {KERN_ELEM, KERN_ELEM, KERN_ELEM}
    };
    QImage newImage(in_image.width(),in_image.height(),QImage::Format_ARGB32);


    const int DK = KERN_SIZE / 2;
        for (int indx_row = 0; indx_row < in_image.height(); indx_row++)
        {
            quint8* ptr_out_row = (quint8*)(out_image.bits()
                    + indx_row * out_image.bytesPerLine());

            for (int indx_col = 0; indx_col < in_image.width(); indx_col++)
            {
                double conv_value = 0;
                for (int indx_ker_row = 0; indx_ker_row < KERN_SIZE; indx_ker_row++)
                {
                    int x = indx_row - DK + indx_ker_row;
                    if (x >= 0 && x < in_image.height())
                    {
                        quint8* ptr_in_row = (quint8*)(in_image.bits()
                            + x * in_image.bytesPerLine());
                        for (int indx_ker_col = 0; indx_ker_col < KERN_SIZE; indx_ker_col++)
                        {
                            int y = indx_col - DK + indx_ker_col;
                            if (y >= 0 && y < in_image.width())
                            {
                                conv_value += ptr_in_row[y] * kernel[indx_ker_row][indx_ker_col];
                            }
                        }
                    }
                }
                 ptr_out_row[indx_col] = (int)conv_value;
            }
        }

}//filter
*/


QRgb Sharpening::convolute(const QList<int> &kernel, const QImage &image, int x, int y)
{
    //https://www.qtcentre.org/threads/24930-Convolution-filter
  int kernelsize = sqrt(kernel.size());
  qreal total = 0;
  qreal red = 0;
  qreal green = 0;
  qreal blue = 0;
  for(int r = -kernelsize/2 ; r<=kernelsize/2; ++r){
    for(int c = -kernelsize/2; c<=kernelsize/2; ++c){
      int kerVal = kernel.at((kernelsize/2+r)*kernelsize+(kernelsize/2+c));
      total+=kerVal;
      red += qRed(image.pixel(x+c, y+r))*kerVal;
      green += qGreen(image.pixel(x+c, y+r))*kerVal;
      blue += qBlue(image.pixel(x+c, y+r))*kerVal;
    }
  }
  if(total==0)
      return qRgb(qBound(0, qRound(red), 255), qBound(0, qRound(green), 255), qBound(0, qRound(blue), 255));
  return qRgb(qBound(0, qRound(red/total), 255), qBound(0, qRound(green/total), 255), qBound(0, qRound(blue/total), 255));
}


void Sharpening::applyS(QImage &img)
{
    //https://www.qtcentre.org/threads/24930-Convolution-filter
      QImage newImage(img.width(),img.height(),QImage::Format_ARGB32);
      QList<int> sharpen;//, blur, laplace;
      sharpen << 0 <<  0 <<  0 <<  0 << 0
          << 0 <<  0 << -1 <<  0 << 0
          << 0 << -1 <<  5 << -1 << 0
          << 0 <<  0 << -1 <<  0 << 0
          << 0 <<  0 <<  0 <<  0 << 0;

      for(int r=2;r<img.height()-2;r++){
          for(int c=2;c<img.width()-2;c++)
          {
            img.setPixel(c, r, convolute(sharpen, img, c, r));
          }
        }

        QLabel lab2;
        lab2.setPixmap(QPixmap::fromImage(img));


}
