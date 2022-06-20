#include "image_processing.h"
#include "ui_image_processing.h"
#include "gaussian_filter.h"
#include "laplacian_filter.h"
#include "sharpening_filter.h"
#include "canny_filter.h"


#include <QString>
#include <QPixmap>
#include <QMessageBox>

ImageProcessing::ImageProcessing(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Image_Processing)
{
    ui->setupUi(this);
//    this->on_pushB_Upload_clicked();
}

ImageProcessing::~ImageProcessing()
{
    delete ui;
} /* ~Image_Processing */

void ImageProcessing::on_pushB_Gaussian_clicked()
{
    GaussianFilter blur(ui->radius_spin->value(), ui->sigma_spin->value()); // radius, sigma ( default)
    blur.apply(this->sourceImage);

    ui->label_image->setPixmap(QPixmap::fromImage(this->sourceImage));
}

void ImageProcessing::on_pushB_Laplacian_clicked()
{
    LaplacianFilter edgeDetection;
    this->sourceImage = edgeDetection.applyLaplacianGaussian(this->sourceImage, 0.5);
    ui->label_image->setPixmap(QPixmap::fromImage(this->sourceImage));
}

void ImageProcessing::on_pushB_Sharp_clicked()
{
    Sharpening sharp;
    sharp.applyS(this->sourceImage);
    ui->label_image->setPixmap(QPixmap::fromImage(this->sourceImage));
}



void ImageProcessing::on_pushB_Upload_clicked()
{
    //get the file image from
    QString filename;

    filename = QFileDialog::getOpenFileName(this,tr("Choose"),"",tr("Images (*.tiff *.png *.jpg *.jpeg)"));

    ui->label_image->setBackgroundRole(QPalette::Base);
    ui->label_image->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label_image->setScaledContents(true);

    //check if it is a valid file
    if (QString::compare(filename, QString()) != 0)
    {
        if(sourceImage.load(filename))
        {
            ui->label_image->setPixmap(QPixmap::fromImage(sourceImage));
        }
        else
        {
            // Error handling
            QMessageBox::critical(this,"Error","Error!");
        }
    }
}/* on_pushB_Upload_clicked */


void ImageProcessing::on_pushB_Download_clicked()
{
    if (!sourceImage.isNull())
    {
       QString fileName;
       fileName =  QFileDialog::getSaveFileName(this, "Save as", "image file", "PNG(*.png);; JPEG(*.jpg *.jpeg);; TIFF(*.tiff *.tif)");
       ui->label_image->grab().save(fileName,0);
        /*
         * NOTE:
         * for now it saves the image depending how we resize our screen and the quaility is not so high!
        */
    }
    else
    {
       QMessageBox::warning(this, "Problem", "File could not be saved!", QMessageBox::Ok);
    }
}/* on_pushB_Download_clicked */


void ImageProcessing::on_pushB_deleteImage_clicked()
{
    if (!sourceImage.isNull())
    {
        sourceImage = QImage();
        ui->label_image->clear(); //this removes the pixmap of the label
    }
    else
    {
       QMessageBox::information(this, "Information", "There is no image to be deleted!",QMessageBox::Cancel);
     }
}/* on_pushB_deleteImage_clicked */



