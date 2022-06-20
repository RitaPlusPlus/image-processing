#include "gradient_filter.h"

GradientFilter::GradientFilter()
{

}

QImage GradientFilter::gradientFilter(const  uchar* imageData,const int width, const int height,const QImage::Format format)
{
    // c = 2 : Sobel ; c = 1 : Prewitt
    const int c = 2;
    const int kernelX[9] ={-1,0,1,
                          -c,0,c,
                          -1,0,1};

    const int kernelY[9] ={-1,-c,-1,
                           0,0,0,
                           1,c,1};

    const int kernelRadius = 1;
    const int kernelWidth = 3;

    QImage* imageFiltered = new QImage(width, height,format);
    uchar* imageFilteredData = imageFiltered->bits();
    for(int i= 0 ; i<width; i++)
    {
        for(int j= 0 ; j<height; j++)
        {
            float gradientX[3] = {0.0f,0.0f,0.0f};
            float gradientY[3] = {0.0f,0.0f,0.0f};
            for(int ki=-kernelRadius; ki<=kernelRadius; ki++)
            {
                int x_k = ki+ kernelRadius;
                int x = fmax(fmin(i+ki,width-1),0);
                for(int kj=-kernelRadius; kj<=kernelRadius; kj++)
                {
                    int y_k = kj+ kernelRadius;
                    int y = fmax(fmin(j+kj,height-1),0);

                    int index = 4*x + y*width *4;
                    int red = imageData[index];
                    int green = imageData[index +1] ;
                    int blue = imageData[index +2] ;

                    float h = kernelX[x_k + y_k*kernelWidth];
                    float hY = kernelY[x_k + y_k*kernelWidth];

                    gradientX[0]+= (red * h);
                    gradientX[1]+=(green * h);
                    gradientX[2]+=(blue * h);

                    gradientY[0]+= (red * hY);
                    gradientY[1]+=(green * hY);
                    gradientY[2]+=(blue * hY);

                }
            }
            gradientX[0] /= (c+2);
            gradientX[1] /= (c+2);
            gradientX[2] /= (c+2);

            gradientY[0] /= (c+2);
            gradientY[1] /= (c+2);
            gradientY[2] /= (c+2);

            int id = 4*i + j*width *4;
            //red
            imageFilteredData[id] = sqrt(pow(gradientX[0],2)+pow(gradientY[0],2));
            //green
            imageFilteredData[id+1] = sqrt(pow(gradientX[1],2)+pow(gradientY[1],2));
            //blue
            imageFilteredData[id+2] =sqrt(pow(gradientX[2],2)+pow(gradientY[2],2));
            //alpha
            imageFilteredData[id+3] = 255.0f;

        }
    }
    return *imageFiltered;
}

