#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <QMainWindow>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Image_Processing; }
QT_END_NAMESPACE

class Image_Processing : public QMainWindow
{
    Q_OBJECT

public:
    Image_Processing(QWidget *parent = nullptr);
    ~Image_Processing();

private slots:

    void on_pushB_Upload_clicked();

    void on_pushB_Download_clicked();

    void on_pushB_deleteImage_clicked();

private:
    Ui::Image_Processing *ui;

    QImage image;
    /*
     * QImage is designed and optimized for I/O,
     * and for direct pixel access and manipulation,
     * while QPixmap is designed and optimized for showing images on screen.
    */
};
#endif // IMAGE_PROCESSING_H
