#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include <QImage>

class MedianFilter
{
    public:
        //! Median filter
        /*!
            Median filter
        */
        MedianFilter();

        //! apply Median filter
        /*!
            apply Median filter
        */
        QImage applyMedianFilter(const unsigned char* image_bits, const int row, const int col, QImage::Format image_format);
};

#endif // MEDIANFILTER_H



