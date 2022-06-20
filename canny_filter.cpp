#include "canny_filter.h"

CannyFilter::CannyFilter()
{
}

CannyFilter::CannyFilter(int w, int h) : w_(w), h_(h), size_(w * h)
{

    G_ = (double*)calloc(w_ * h_, sizeof(double));
    M_ = (double*)calloc(w_ * h_, sizeof(double));
    s_ = (unsigned char*)calloc(w_ * h_, sizeof(unsigned char));
}

CannyFilter::~CannyFilter()
{
    free(G_);
    free(M_);
    free(s_);
}

unsigned char* CannyFilter::edges(unsigned char* dst, const unsigned char* src,
                            CannyFilter::NoiseFilter kernel_size, int weak_threshold,
                            int strong_threshold)
{
    int offset_xy = 1;  // for kernel = 3
    int8_t* kernel = (int8_t*)Gaus3x3;
    int kernel_div = Gaus3x3Div;

    if (kernel_size == NoiseFilter::Gaus5x5) {
        offset_xy = 2;
        kernel = (int8_t*)Gaus5x5;
        kernel_div = Gaus5x5Div;
    }

    // gaussian filter

    for (int x = 0; x < w_; x++) {
        for (int y = 0; y < h_; y++) {
            int pos = x + (y * w_);
            if (x < offset_xy || x >= (w_ - offset_xy) || y < offset_xy ||
                y >= (h_ - offset_xy)) {
                dst[pos] = src[pos];
                continue;
            }
            int convolve = 0;
            int k = 0;
            for (int kx = -offset_xy; kx <= offset_xy; kx++) {
                for (int ky = -offset_xy; ky <= offset_xy; ky++) {
                    convolve += (src[pos + (kx + (ky * w_))] * kernel[k]);
                    k++;
                }
            }

            dst[pos] = (unsigned char)((double)convolve / (double)kernel_div);
        }
    }

    // apply sobel kernels
    offset_xy = 1;  // 3x3
    for (int x = offset_xy; x < w_ - offset_xy; x++) {
        for (int y = offset_xy; y < h_ - offset_xy; y++) {
            double convolve_X = 0.0;
            double convolve_Y = 0.0;
            int k = 0;
            int src_pos = x + (y * w_);

            for (int ky = -offset_xy; ky <= offset_xy; ky++) {
                for (int kx = -offset_xy; kx <= offset_xy; kx++) {
                    convolve_X += dst[src_pos + (kx + (ky * w_))] * Gx[k];
                    convolve_Y += dst[src_pos + (kx + (ky * w_))] * Gy[k];

                    k++;
                }
            }

            // gradient hypot & direction
            int segment = 0;

            if (convolve_X == 0.0 || convolve_Y == 0.0) {
                G_[src_pos] = 0;
            } else {
                G_[src_pos] = ((std::sqrt((convolve_X * convolve_X) +
                                          (convolve_Y * convolve_Y))));
                double theta = std::atan2(
                    convolve_Y, convolve_X);  // radians. atan2 range: -PI,+PI,
                                              // theta : 0 - 2PI
                theta = theta * (360.0 / (2.0 * M_PI));  // degrees

                if ((theta <= 22.5 && theta >= -22.5) || (theta <= -157.5) ||
                    (theta >= 157.5)) {
                    segment = 1;  // "-"
                } else if ((theta > 22.5 && theta <= 67.5) ||
                           (theta > -157.5 && theta <= -112.5)) {
                    segment = 2;  // "/"
                } else if ((theta > 67.5 && theta <= 112.5) ||
                           (theta >= -112.5 && theta < -67.5)) {
                    segment = 3;  // "|"
                } else if ((theta >= -67.5 && theta < -22.5) ||
                           (theta > 112.5 && theta < 157.5)) {
                    segment = 4;  // "\"
                } else {
                    std::cout << "error " << theta << std::endl;
                }
            }

            s_[src_pos] = (unsigned char)segment;
        }
    }

    // local maxima: non maxima suppression
    memcpy (M_, G_, w_ * h_ * sizeof(double));

    for (int x = 1; x < w_ - 1; x++) {
        for (int y = 1; y < h_ - 1; y++) {
            int pos = x + (y * w_);

            switch (s_[pos]) {
                case 1:
                    if (G_[pos - 1] >= G_[pos] ||
                        G_[pos + 1] > G_[pos]) {
                        M_[pos] = 0;
                    }
                    break;
                case 2:
                    if (G_[pos - (w_ - 1)] >= G_[pos] ||
                        G_[pos + (w_ - 1)] > G_[pos]) {
                        M_[pos] = 0;
                    }
                    break;
                case 3:
                    if (G_[pos - (w_)] >= G_[pos] ||
                        G_[pos + (w_)] > G_[pos]) {
                        M_[pos] = 0;
                    }
                    break;
                case 4:
                    if (G_[pos - (w_ + 1)] >= G_[pos] ||
                        G_[pos + (w_ + 1)] > G_[pos]) {
                        M_[pos] = 0;
                    }
                    break;
                default:
                    M_[pos] = 0;
                    break;
            }
        }
    }


    // double threshold
    for (int x = 0; x < w_; x++) {
        for (int y = 0; y < h_; y++) {
            int src_pos = x + (y * w_);
            if (M_[src_pos] > strong_threshold) {
                dst[src_pos] = 255;
            } else if (M_[src_pos] > weak_threshold) {
                dst[src_pos] = 100;
            } else {
                dst[src_pos] = 0;
            }
        }
    }

    // edges with hysteresis
    for (int x = 1; x < w_ - 1; x++) {
        for (int y = 1; y < h_ - 1; y++) {
            int src_pos = x + (y * w_);
            if (dst[src_pos] == 255) {
                dst[src_pos] = 255;
            } else if (dst[src_pos] == 100) {
                if (dst[src_pos - 1] == 255 || dst[src_pos + 1] == 255 ||
                    dst[src_pos - 1 - w_] == 255 ||
                    dst[src_pos + 1 - w_] == 255 || dst[src_pos + w_] == 255 ||
                    dst[src_pos + w_ - 1] == 255 ||
                    dst[src_pos + w_ + 1] == 255) {
                    dst[src_pos] = 255;
                } else {
                    dst[src_pos] = 0;
                }
            } else {
                dst[src_pos] = 0;
            }
        }
    }

    return dst;
}
