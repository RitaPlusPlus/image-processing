#ifndef HORIZONTALSOBELFILTER_H
#define HORIZONTALSOBELFILTER_H

#include <QImage>

class horizontalSobelFilter
{
    public:
        //! Horizontal Sobel Filter
        /*!
            Horizontal Sobel Filter
        */
        horizontalSobelFilter();


        //! Horizontal Sobel Filter kernel
        /*!
            Horizontal Sobel Filter kernel
        */
        QImage horizontalSobelGradientFilter(const unsigned char* image, const int width, const int height, const QImage::Format f);


        //! apply Horizontal Sobel Filter
        /*!
            apply Horizontal Sobel Filter
        */
        QImage applyHSFilter( const unsigned char *image,
                              const int width,
                              const int height,
                              const QImage::Format f,
                              const int radius_kernel,
                              const int kernel[],
                              const double parameter_kernel,
                              QColor (*convolution)(  const unsigned char *image,
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

        //! convolution function
        /*!
            convolution function
        */
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

#endif // HORIZONTALSOBELFILTER_H
