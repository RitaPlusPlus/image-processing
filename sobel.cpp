#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QTextStream>
#include <QString>

#include <cmath>

using namespace std;

const int INTENS_MIN = 0;
const int INTENS_MAX = 255;
const int KERN_SIZE = 9;

double sobel_x[][KERN_SIZE] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
};

double sobel_y[][KERN_SIZE] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};

const QString file_name = "../gray_lenna.png";

void sobel(const QImage &in_image, QImage &out_image)
{
    const int DK = KERN_SIZE / 2;
    for (int indx_row = 0; indx_row < in_image.height(); indx_row++)
    {
        quint8* ptr_out_row = (quint8*)(out_image.bits() 
                + indx_row * out_image.bytesPerLine());
        for (int indx_col = 0; indx_col < in_image.width(); indx_col++)
        {
            double grad_x = 0;
            double grad_y = 0;
            for (int indx_ker_row = 0; indx_ker_row < KERN_SIZE; indx_ker_row++)
            {
                int x = indx_row - DK + indx_ker_row;
                if (x >= 0 && x < in_image.height())
                {
                    quint8* ptr_in_row = (quint8*)(in_image.bits() 
                        + x * in_image.bytesPerLine());
                    for (int indx_ker_col = 0; indx_ker_col < KERN_SIZE; indx_ker_col++)
                    {                    
                        int y = indx_col - DK + indx_ker_col;
                        if (y >= 0 && y < in_image.width())
                        {
                            grad_x += ptr_in_row[y] * sobel_x[indx_ker_row][indx_ker_col];
                            grad_y += ptr_in_row[y] * sobel_y[indx_ker_row][indx_ker_col];
                        } 
                    }
                }
            }
            ptr_out_row[indx_col] = (int)(sqrt(grad_x * grad_x + grad_y * grad_y));  
        }
    }    
}//filter

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QImage in_image;
    QLabel label;

    if (in_image.load(file_name))
    {
        QTextStream(stdout) << "Image loaded: " << file_name << endl;
        QTextStream(stdout) << "Format: " << in_image.format() << endl;

        QImage out_image(in_image.width(), in_image.height(), QImage::Format_Grayscale8);

        if (in_image.format() == QImage::Format_Grayscale8)
        {
            sobel(in_image, out_image);   
        } 
             
        label.setPixmap(QPixmap::fromImage(out_image));
    }
    else
    {
        QTextStream(stdout) << "Cannot load image: " << file_name << endl;
    }

    label.show();

    return app.exec();
}//main



