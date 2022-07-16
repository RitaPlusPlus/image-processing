#include "laplacian_filter.h"

LaplacianFilter::LaplacianFilter()
{

}/* LaplacianFilter */

/*Gaussian Laplacian edge detection*/
QImage LaplacianFilter::applyLaplacianGaussian(const QImage &image,double scale)
{
    QImage newImage(image.width(),image.height(),QImage::Format_ARGB32);
    QColor color0;
    int templt[5][5] = {
        {0,0,-1,0,0},
        {0,-1,-2,-1,0},
        {-1,-2,16,-2,-1},
        {0,-1,-2,-1,0},
        {0,0,-1,0,0}
    };

    int templtsize = 5;
    for(int y = templtsize/2; y <image.height()-templtsize/2; y++)
    {
        for(int x = templtsize/2; x <image.width()-templtsize/2;x++)
        {
            int r =0;
            int g = 0;
            int b = 0;
            for(int j = -templtsize/2; j <= templtsize/2;j++)
            {
                for(int i = -templtsize/2; i <= templtsize/2;i++)
                {
                       color0 = QColor(image.pixel(x + i,y + j));
                       r += color0.red() * templt[i + templtsize/2][j + templtsize/2];
                       g += color0.green() * templt[i + templtsize/2][j + templtsize/2];
                       b += color0.blue() * templt[i + templtsize/2][j + templtsize/2];
                }
            }
            r*=scale;
            g*=scale;
            b*=scale;
            r = qBound(0,r,255);
            g = qBound(0,g,255);
            b = qBound(0,b,255);
            newImage.setPixel(x,y,qRgb(r,g,b));
        }
    }
    return newImage;
}/* applyLaplacianGaussian */

/*Laplace edge detection scale scale to scale the difference result mode is to select which method 0 only shows positive edges, 1 only shows negative edges, 2 shows all edges, 3 uses both high gray and low gray Show positive and negative edges separately*/
QImage LaplacianFilter::applyLaplacian(const QImage &image,double scale,int mode)
{
    QImage newImage(image.width(),image.height(),QImage::Format_ARGB32);
    QColor color0;
    int templt[3][3] = {
        {1,1,1},
        {1,-8,1},
        {1,1,1}
    };
    int templtsize = 3;
    for(int y = templtsize/2; y <image.height()-templtsize/2; y++)
    {
        for(int x = templtsize/2; x <image.width()-templtsize/2;x++)
        {
            int r =0;
            int g = 0;
            int b = 0;
            for(int j = -templtsize/2; j <= templtsize/2;j++)
            {
                for(int i = -templtsize/2; i <= templtsize/2;i++)
                {
                       color0 = QColor(image.pixel(x + i,y + j));
                       r += color0.red() * templt[i + templtsize/2][j + templtsize/2];
                       g += color0.green() * templt[i + templtsize/2][j + templtsize/2];
                       b += color0.blue() * templt[i + templtsize/2][j + templtsize/2];
                }
            }
           r*= scale;
           g*=scale;
           b*=scale;
           r = qBound(-255,r,255);
           g = qBound(-255,g,255);
           b = qBound(-255,b,255);
           switch (mode) {
           case 0:
               if(r<0) r = 0;

               if(g<0) g = 0;

               if(b<0) b = 0;
               break;
           case 1:
               if(r>0) r = 0;
               r = -r;

               if(g>0) g = 0;
               g = -g;

               if(b>0) b = 0;
               b = -b;
               break;
           case 2:
               if(r<0) r = -r;

               if(g<0) g = -g;

               if(b<0) b = -b;
               break;
           case 3:
               if(r<0) r = 128 + r/2;

               if(g<0) g = 128 + g/2;

               if(b<0) b = 128 + b/2;
               break;
           default:
               break;
           }
            newImage.setPixel(x,y,qRgb(r,g,b));
        }
    }
    return newImage;
}/* applyLaplacian */
