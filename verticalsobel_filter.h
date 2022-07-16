#ifndef VERTICALSOBELFILTER_H
#define VERTICALSOBELFILTER_H

#include <QImage>

class verticalSobelFilter
{
    public:
        //! Vertical Sobel Filter
        /*!
            Vertical Sobel Filter
        */
        verticalSobelFilter();


        //! Vertical Sobel Filter kernel
        /*!
            Vertical Sobel Filter kernel
        */
        QImage verticalSobelGradientFilter(const unsigned char* image, const int width, const int height, const QImage::Format f);


        //! apply Vertical Sobel Filter
        /*!
            apply Vertical Sobel Filter
        */
        QImage applyVSFilter( const unsigned char *image,
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

#endif // VERTICALSOBELFILTER_H
