#include "horizontalsobel_filter.h"

horizontalSobelFilter::horizontalSobelFilter()
{

}


QImage horizontalSobelFilter::horizontalSobelGradientFilter(const  uchar* imageData,const int width, const int height,const QImage::Format format)
{
    const int c = 2;

    const int kernel[9] ={-1,0,1,
                          -c,0,c,
                          -1,0,1};


    return applyFilter(imageData, width, height, format, 1, kernel, c+2 , &horizontalSobelFilter::applyConvolution);
}


QImage horizontalSobelFilter::applyFilter(const uchar *imageData, const int width, const int height, const QImage::Format format, const int kernelRadius, const int kernel[], const float kernelParameter,
                                          QColor (*convolution)(const uchar *,const int, const int,
                                                               const int , const int[], const float ,const int ,
                                                               const int ,const int ))
{
    const int kernelWidth = 2*kernelRadius +1;
    QImage* imageFiltered = new QImage(width, height, format);
    uchar* imageFilteredData = imageFiltered->bits();

    for(int x= 0 ; x<width; x++)
    {
        for(int y= 0 ; y<height; y++)
        {
            QColor color = convolution(imageData,width,height,kernelRadius,kernel,kernelParameter,kernelWidth,x,y);
            int index = 4*x + y * width*4 ;
            imageFilteredData[index] = color.red();
            imageFilteredData[index +1] = color.green();
            imageFilteredData[index +2] = color.blue();
            imageFilteredData[index +3] = color.alpha();
        }
    }
    return *imageFiltered;
}

// A simple convolution function
QColor horizontalSobelFilter::applyConvolution(const uchar *imageData,const int width, const int height,
                                               const int kernelRadius, const int kernel[], const float kernelParameter,const int kernelWidth,
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

            float h = kernel[iKernel+ jKernel*kernelWidth] / kernelParameter;
            r = fminf( r + imageColor.red()   * h, 255.0f);
            g = fminf( g + imageColor.green()   * h, 255.0f);
            b = fminf( b + imageColor.blue()   * h, 255.0f);

        }
    }
    return QColor(abs(r),abs(g),abs(b));
}
