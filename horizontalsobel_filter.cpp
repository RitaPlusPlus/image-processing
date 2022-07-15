#include "horizontalsobel_filter.h"

horizontalSobelFilter::horizontalSobelFilter()
{

}// Horizontal Sobel Filter


QImage horizontalSobelFilter::horizontalSobelGradientFilter(const  unsigned char* imageData,const int width, const int height,const QImage::Format f)
{
    const int c = 2;

    const int kernel[9] ={-1,0,1,
                          -c,0,c,
                          -1,0,1};

    return applyHSFilter(imageData, width, height, f, 1, kernel, c+2 , &horizontalSobelFilter::applyConv);
}// Horizontal Sobel Filter kernel


QImage horizontalSobelFilter::applyHSFilter(const unsigned char *imageData, const int width, const int height, const QImage::Format f, const int kernelRadius, const int kernel[], const double kernelParameter,
                                          QColor (*convolution)(const unsigned char *,const int, const int,
                                                               const int , const int[], const double ,const int ,
                                                               const int ,const int ))
{
    const int kernelWidth = 2*kernelRadius +1;
    QImage* newImage = new QImage(width, height, f);
    unsigned char* newImageData = newImage->bits();

    for(int x= 0 ; x<width; x++)
    {
        for(int y= 0 ; y<height; y++)
        {
            QColor color = convolution(imageData,width,height,kernelRadius,kernel,kernelParameter,kernelWidth,x,y);
            int index = 4*x + y * width*4 ;
            newImageData[index] = color.red();
            newImageData[index +1] = color.green();
            newImageData[index +2] = color.blue();
            newImageData[index +3] = color.alpha();
        }
    }
    return *newImage;
}// apply Horizontal Sobel Filter

// A simple convolution function
QColor horizontalSobelFilter::applyConv(const unsigned char *imageData,const int width, const int height,
                                               const int kernelRadius, const int kernel[], const double kernelParameter,const int kernelWidth,
                                               const int x,const int y)
{
    int r = 0;
    int g = 0;
    int b = 0;

    for(int kx=-kernelRadius; kx<=kernelRadius; kx++)
    {
        int iKernel = kx + kernelRadius;
        //index i of the neighboor pixel
        int i = fmax(fmin(x+kx,width-1),0);
        for(int ky=-kernelRadius; ky<=kernelRadius; ky++)
        {
            int jKernel = ky + kernelRadius;
            //index j of the neighboor pixel
            int j = fmax(fmin(y+ky,height-1),0);
            QColor imageColor =  QColor(imageData[4*i +j* width*4], imageData[4*i +j* width*4 +1],imageData[4*i +j* width*4+2] ,imageData[4*i +j* width*4+3]) ;

            double h = kernel[iKernel+ jKernel*kernelWidth] / kernelParameter;
            r = fminf( r + imageColor.red()   * h, 255.0f);
            g = fminf( g + imageColor.green()   * h, 255.0f);
            b = fminf( b + imageColor.blue()   * h, 255.0f);

        }
    }
    return QColor(abs(r),abs(g),abs(b));
}
