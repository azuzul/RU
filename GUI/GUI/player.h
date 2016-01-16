#ifndef PLAYER_H
#define PLAYER_H
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <QLabel>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace cv;

class Player : public QThread
{ Q_OBJECT

private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    VideoCapture capture;
    Mat RGBframe;
    QImage img;
    QImage img_gmm;
    int video;

    //Some constants for the algorithm
    const double pi = 3.142;
    const double cthr = 0.00001;
    const double alpha = 0.002;
    const double cT = 0.05;
    const double covariance0 = 11.0;
    const double cf = 0.1;
    const double cfbar = 1.0-cf;
    const double temp_thr = 9.0*covariance0*covariance0;
    const double prune = -alpha*cT;
    const double alpha_bar = 1.0-alpha;
    //Temperory variable
    int overall = 0;

    //Structure used for saving various components for each pixel
    struct gaussian
    {
        double mean[3], covariance;
        double weight;								// Represents the measure to which a particular component defines the pixel value
        gaussian* Next;
        gaussian* Previous;
    } *ptr = NULL, *start_gmm = NULL, *rear = NULL, *g_temp = NULL, *save = NULL, *next = NULL, *previous = NULL, *nptr = NULL, *temp_ptr = NULL;

    struct Node
    {
        gaussian* pixel_s;
        gaussian* pixel_r;
        int no_of_components;
        Node* Next;
    } *N_ptr = NULL, *N_start = NULL, *N_rear = NULL;


    struct Node1
    {
        cv::Mat gauss;
        int no_of_comp;
        Node1* Next;
    } *N1_ptr = NULL, *N1_start = NULL, *N1_rear = NULL;


signals:
    void processedImage(const QImage &image, const QImage &image_gmm, int video);

protected:
    void run();
    void msleep(int ms);

public:
    Player(QObject *parent = 0, int video = 10);
    ~Player();

    bool loadVideo(string filename);
    void Play();
    void Stop();
    bool isStopped() const;

    //Some function associated with the structure management
    Node* Create_Node(double info1, double info2, double info3);
    void Insert_End_Node(Node* np);
    gaussian* Create_gaussian(double info1, double info2, double info3);
    void Insert_End_gaussian(gaussian* nptr);
    gaussian* Delete_gaussian(gaussian* nptr);

    void gmm();
};

#endif // PLAYER_H
