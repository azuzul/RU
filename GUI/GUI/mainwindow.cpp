#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/opencv.hpp>

#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myPlayer = new Player(0, 0);
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage,QImage,int)),
                     this, SLOT(updatePlayerUI(QImage,QImage,int)));

    myPlayer1 = new Player(0, 1);
    QObject::connect(myPlayer1, SIGNAL(processedImage(QImage,QImage,int)),
                     this, SLOT(updatePlayerUI(QImage,QImage,int)));
}

void MainWindow::updatePlayerUI(QImage img, QImage img_gmm, int video)
{
    if (!img.isNull())
    {
        if(video == 0) {
            ui->video->setAlignment(Qt::AlignCenter);
            ui->video->setPixmap(QPixmap::fromImage(img).scaled(ui->video->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
            ui->video2->setAlignment(Qt::AlignCenter);
            ui->video2->setPixmap(QPixmap::fromImage(img_gmm).scaled(ui->video2->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
        } else if(video == 1) {
            ui->video1->setAlignment(Qt::AlignCenter);
            ui->video1->setPixmap(QPixmap::fromImage(img).scaled(ui->video1->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
            ui->video3->setAlignment(Qt::AlignCenter);
            ui->video3->setPixmap(QPixmap::fromImage(img_gmm).scaled(ui->video3->size(), Qt::KeepAspectRatio, Qt::FastTransformation));
        }
    }
}

MainWindow::~MainWindow()
{
    delete myPlayer;
    delete myPlayer1;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,
                                                    tr("Open Video"), ".",
                                                    tr("Video Files (*.avi *.mpg *.mp4)"));


    if (!filenames.isEmpty()){
        if (!myPlayer->loadVideo(filenames[0].toLatin1().data()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }

        if(filenames.size() < 2) {
            if (!myPlayer1->loadVideo(0))
            {
                QMessageBox msgBox;
                msgBox.setText("The selected video could not be opened!");
                msgBox.exec();
            }
        } else {
            if (!myPlayer1->loadVideo(filenames[1].toLatin1().data()))
            {
                QMessageBox msgBox;
                msgBox.setText("The selected video could not be opened!");
                msgBox.exec();
            }
        }
    } else {
        if(!myPlayer->loadVideo(0)) {

        }
        if(!myPlayer1->loadVideo(1)) {

        }
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    myPlayer->alpha = ui->param_alpha->text().toDouble();
    myPlayer->cT = ui->param_cT->text().toDouble();
    //myPlayer->covariance0 = ui->param_covariance0->text().toDouble();
    myPlayer->covariance0 = 11.0;
    myPlayer->cf = ui->param_cF->text().toDouble();

    myPlayer1->alpha = ui->param_alpha->text().toDouble();
    myPlayer1->cT = ui->param_cT->text().toDouble();
    //myPlayer1->covariance0 = ui->param_covariance0->text().toDouble();
    myPlayer1->covariance0 = 11.0;
    myPlayer1->cf = ui->param_cF->text().toDouble();

    if (myPlayer->isStopped())
    {
        myPlayer->Play();
        ui->pushButton_2->setText(tr("Stop"));
    }else
    {
        myPlayer->Stop();
        ui->pushButton_2->setText(tr("Play"));
    }

    if (myPlayer1->isStopped())
    {
        myPlayer1->Play();
        ui->pushButton_2->setText(tr("Stop"));
    }else
    {
        myPlayer1->Stop();
        ui->pushButton_2->setText(tr("Play"));
    }
}
