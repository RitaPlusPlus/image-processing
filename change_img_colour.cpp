#include "change_img_colour.h"

BlckWhtclr::BlckWhtclr()
{
} /* BlckWhtclr */

QImage BlckWhtclr::setBlckWht(const unsigned char* image, const int width, const int height, const QImage::Format f)
{
    QImage* new_image = new QImage(width, height, f);
    unsigned char* bw_image = new_image->bits(); /* bw stands for a black-white coloured image */

    for(int i= 0; i < height * width * 4; i += 4 )
    {
        double bw_value = 0.299 * image[i] + 0.587 * image[i + 1] + 0.114 * image[i + 2];
        /* Red */
        bw_image[i] = bw_value;
        /* Green */
        bw_image[i + 1] = bw_value;
        /* Blue */
        bw_image[i + 2] = bw_value;
        /* alpha */
        bw_image[i + 3] = image[i + 3];
    }
    return (*new_image);
} /* setBlckWht */
