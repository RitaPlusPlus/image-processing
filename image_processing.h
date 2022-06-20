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

    void on_pushB_Gaussian_clicked();

    void on_pushB_Laplacian_clicked();

    void on_pushB_Upload_clicked();

    void on_pushB_Download_clicked();

    void on_pushB_deleteImage_clicked();

    void on_pushB_Mean_clicked();

    void on_pushB_Gradient_clicked();

    void on_pushB_convertGS_clicked();

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
