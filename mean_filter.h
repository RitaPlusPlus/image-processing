#ifndef MEAN_FILTER_H
#define MEAN_FILTER_H

#include <QImage>

using namespace std;

class MeanFilter
{
    public:
        //! Mean filter
        /*!
            Mean filter
        */
        MeanFilter();

        //! apply Mean Blur filter
        /*!
            apply Mean Blur filter
        */
        QImage applyMeanBlurFilter(const unsigned char* image, const int width, const int height, const QImage::Format f);

        //! apply Mean
        /*!
            apply Mean
        */
        QImage applyMean(  const unsigned char *image,
                           const int width,
                           const int height,
                           const QImage::Format f,
                           const int radius_kernel,
                           const int kernel[],
                           const double parameter_kernel,
                           QColor (*conv)(  const unsigned char *image,
                                            const int width,
                                            const int height,
                                            const int radius_kernel,
                                            const int kernel[],
                                            const double parameter_kernel,
                                            const int width_kernel,
                                            const int x,
                                            const int y
                                        )
                          );

        /* convolution function */
        static QColor conv( const unsigned char *image,
                            const int width,
                            const int height,
                            const int radius_kernel,
                            const int kernel[],
                            const double parameter_kernel,
                            const int width_kernel,
                            const int x,
                            const int y
                          );
};

#endif // MEAN_FILTER_H
