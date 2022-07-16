#include <vector>
#include "median_filter.h"


MedianFilter::MedianFilter()
{

}

QImage MedianFilter::applyMedianFilter(const uchar* imageData, const int width, const int height, QImage::Format format)
{
    QImage filteredImage(width,height, format);
    uchar* filteredImageData = filteredImage.bits();
    int kernelRadius = 1;

    //list of neighborhood values
    std::vector<int> medianList;
    medianList.reserve(9);
    for(int i=0; i<width; i++)
    {
        for(int j=0; j<height; j++)
        {
            medianList.clear();

            for(int ki=-kernelRadius; ki<=kernelRadius; ki++)
            {
                int x = fmax(fmin(i+ki,width-1),0);
                for(int kj=-kernelRadius; kj<=kernelRadius; kj++)
                {
                    int y = fmax(fmin(j+kj,height-1),0);
                    int index = 4*x+ y*width*4;
                    medianList.push_back(imageData[index]);
                }
            }
            // Find the median value
            std::sort(medianList.begin(),medianList.end());
            int medianValue = medianList[medianList.size()/2 ];
            int id = 4*i+ j*width*4;
            filteredImageData[id] = medianValue;
            filteredImageData[id+1] = medianValue;
            filteredImageData[id+2] = medianValue;
            filteredImageData[id+3] = 255.0f;
        }
    }
    return filteredImage;
}
