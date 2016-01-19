#ifndef PLAYER_H
#define PLAYER_H
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <QLabel>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "gmm.h"

using namespace cv;

class Player : public QThread
{ Q_OBJECT

private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    VideoCapture capture;
    Mat RGBframe;
    QImage img;
    QImage img_gmm;
    int video;

signals:
    void processedImage(const QImage &image, const QImage &image_gmm, int video);

protected:
    void run();
    void msleep(int ms);

public:
    Player(QObject *parent = 0, int video = 10, double alpha = 0.002, double cT = 0.05, double covariance0 = 11.0, double cf = 0.1, int frameRate = 30);
    ~Player();

    bool loadVideo(string filename);
    void Play();
    void Stop();
    bool isStopped() const;

    double alpha;
    double cT;
    double covariance0;
    double cf;
    int frameRate;

    void gmm();
};

#endif // PLAYER_H
