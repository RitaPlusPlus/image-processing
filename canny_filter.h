#ifndef CANNY_FILTER_H
#define CANNY_FILTER_H

#include <QTextStream>
#include <QImage>


#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string.h>
#include <cstdint>
#include <iomanip>

using namespace std;

//http://www.pages.drexel.edu/~nk752/Research/cannyTut2.html
//https://turbosnu.wordpress.com/2016/01/12/image-processing-canny-edge-detection-in-c/
//https://github.com/brunokeymolen/canny/blob/master/canny.cpp
class CannyFilter
{
    public:
        CannyFilter();
        CannyFilter(int w, int h);
        virtual ~CannyFilter();

        enum class NoiseFilter {
                                    Gaus3x3,
                                    Gaus5x5
                                };

        unsigned char* edges(
                             unsigned char* dst,
                             const unsigned char* src,
                             NoiseFilter kernel_size,
                             int weak_threshold = 50,
                             int strong_threshold = 200
                            );




    private:

        int w_;
        int h_;
        int size_;
        double* G_;
        double* M_;
        unsigned char* s_;


            const int Gx[9] = {-1, 0, 1,
                                 -2, 0, 2,
                                 -1, 0, 1};

            const int Gy[9] = { 1, 2, 1,
                                  0, 0, 0,
                                 -1,-2,-1};

            //Gausian blur
            //3 x 3 kernel
            const int Gaus3x3[9] = { 1, 2, 1,
                                       2, 4, 2,   // * 1/16
                                       1, 2, 1};
            const int Gaus3x3Div = 16;


            const int Gaus5x5[25] = { 	2,  4,  5,  4, 2,
                                        4,  9, 12,  9, 4,
                                        5, 12, 15, 12, 5, // * 1/159
                                        4,  9, 12,  9, 4,
                                        2,  4,  5,  4, 2 };

            const int Gaus5x5Div = 159;

};

#endif // CANNY_FILTER_H
