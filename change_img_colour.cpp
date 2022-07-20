#include "change_img_colour.h"

GrayscaleImg::GrayscaleImg()
{
} /* GrayscaleImg */

QImage GrayscaleImg::setGrscl(const unsigned char* image, const int width, const int height, const QImage::Format f)
{
    QImage* new_image = new QImage(width, height, f);
    unsigned char* grayscale_image = new_image->bits(); /* bits() returns a pointer to the first pixel data. This is equivalent to scanLine(0).
                                                  * This function performs a deep copy of the shared pixel data,
                                                  * thus ensuring that this QImage is the only one using the current return value.
                                                 */


    for (int i = 0; i < height * width * 4; i += 4 ) /* 4 -> RGBA */
    {
        /* converting RGBА to Greyscale
         * The Weighted method (Luminosity method) weighs red, green, and blue according to their wavelengths,
         * following is the formula: Grayscale = 0.299R + 0.587G + 0.114B.
        */
        double gr_value = 0.299 * image[i] + 0.587 * image[i + 1] + 0.114 * image[i + 2];
        /*
         * An RGBA color value is specified with: rgba(red, green, blue, alpha) i.e. 4 byte colour.
         * The value of the alpha parameter ranges from 0.0 (fully transparent) to 1.0. (fully opaque).
        */
        /* Red */
        grayscale_image[i] = gr_value;
        /* Green */
        grayscale_image[i + 1] = gr_value;
        /* Blue */
        grayscale_image[i + 2] = gr_value;
        /* alpha */
        grayscale_image[i + 3] = image[i + 3];
    }
    return (*new_image);
} /* setGrscl */
