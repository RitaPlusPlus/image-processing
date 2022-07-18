#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <QMainWindow>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Image_Processing; }
QT_END_NAMESPACE

class ImageProcessing : public QMainWindow
{
    Q_OBJECT

    public:
        ImageProcessing(QWidget *parent = nullptr);
        ~ImageProcessing();

    private slots:
        //! Click handler on Gaussian filter selected
        /*!
             apply Gaussian filter
        */
        void on_pushB_Gaussian_clicked();

        //! Click handler on Laplacian filter selected
        /*!
             apply Laplacian filter
        */
        void on_pushB_Laplacian_clicked();

        //! Click handler on Mean filter selected
        /*!
             apply Mean filter
        */
        void on_pushB_Mean_clicked();

        //! Click handler on Median filter selected
        /*!
             apply Median filter
        */
         void on_pushB_Noise_clicked();

        //! Click handler on Gradient filter selected
        /*!
             apply Gradient filter
        */
        void on_pushB_Gradient_clicked();

        //! Click handler on horizontal Sobel filter selected
        /*!
             apply horizontal Sobel filter
        */
        void on_pushB_hSobel_clicked();

        //! Click handler on vertical Sobel filter selected
        /*!
             apply vertical Sobel filter
        */
        void on_pushB_vSobel_clicked();

        //! Click handler on Convert an image to Greyscale
        /*!
            set the image to be black-and-white coloured
        */
        void on_pushB_convertGS_clicked();

        //! Click handler on Upload clicked
        /*!
             upload an image
        */
        void on_pushB_Upload_clicked();

        //! Click handler on Download clicked
        /*!
             download the image
        */
        void on_pushB_Download_clicked();

        //! Click handler on Delete clicked
        /*!
             delete the image
        */
        void on_pushB_deleteImage_clicked();



private:
        Ui::Image_Processing *ui;

        QImage sourceImage;
        /*
         * QImage is designed and optimized for I/O,
         * and for direct pixel access and manipulation,
         * while QPixmap is designed and optimized for showing images on screen.
        */
};
#endif // IMAGE_PROCESSING_H
