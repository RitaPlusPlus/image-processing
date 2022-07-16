#include <vector>
#include "median_filter.h"


MedianFilter::MedianFilter()
{

}

QImage MedianFilter::applyMedianFilter(const uchar* image_bits, const int row, const int col, QImage::Format image_format)
{
    QImage new_image(row ,col , image_format);
    uchar* new_image_bits = new_image.bits();
    std::vector<int> median;
    median.reserve(9);
    int kernel = 1;


    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            median.clear();
            for(int ki = -kernel; ki <= kernel; ki++)
            {
                int x = fmax(fmin(i + ki, row - 1), 0);
                for(int kj = -kernel; kj <= kernel; kj++)
                {
                    int y = fmax(fmin(j + kj, col - 1) , 0);
                    int index = 4 * x + y * row * 4;
                    median.push_back(image_bits[index]);
                }
            }

            std::sort(median.begin(),median.end());

            int median_elem = median[median.size() /2 ];
            int id = 4 * i + j * row * 4;

            new_image_bits[id] = median_elem;
            new_image_bits[id+1] = median_elem;
            new_image_bits[id+2] = median_elem;
            new_image_bits[id+3] = 255.0f;
        }
    }
    return new_image;
}
