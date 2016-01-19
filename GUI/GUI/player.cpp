#include "player.h"
#include <opencv2/features2d/features2d.hpp>
#include <vector>
#include <unistd.h>
#include <iostream>

Player::Player(QObject *parent,int video, double alpha, double cT, double covariance0, double cf, int frameRate)
    : QThread(parent)
{
    stop = true;
    this->video=video;

    this->alpha = alpha;
    this->cT = cT;
    this->covariance0 = covariance0;
    this->cf = cf;
    this->frameRate = frameRate;
}

bool Player::loadVideo(string filename){

//    if(video == 0) {
//        capture.open(0);
//    } else {
        capture.open(filename);
//    }
    if(capture.isOpened()){
        frameRate = (int)capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    return false;
}

void Player::Play(){
    if(!isRunning()) {
        if(isStopped()) {
            stop = false;
        }
        start(LowPriority);
    }
}

void Player::run()
{
//    frameRate = 30;
//    int delay = (1000/frameRate);
//    std::cout << frameRate << std::endl;

    gmm();
}

Player::~Player()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void Player::Stop()
{
    stop = true;
}

void Player::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

bool Player::isStopped() const{
    return this->stop;
}

void Player::gmm() {
    int i,j,k;
    i=j=k=0;

    GMM gmm(this->alpha, this->cT, this->covariance0, this->cf);

    std::cout << "Parametar alpha: " << gmm.alpha << std::endl;
    std::cout << "Parametar cT: " << gmm.cT << std::endl;
    std::cout << "Parametar covariance0: " << gmm.covariance0 << std::endl;
    std::cout << "Parametar cF: " << gmm.cf << std::endl;


    int delay = (1000/this->frameRate);
    //    std::cout << frameRate << std::endl;

    // Declare matrices to store original and resultant binary image
    cv::Mat orig_img, bin_img;

    //Checking if input source is valid
    if(!capture.read(orig_img))
    {
        std::cout << " Can't recieve input from source ";
        exit(0);
    }

    //Recieveing input from the source and converting it to grayscale
    cv::cvtColor(orig_img, orig_img, CV_BGR2YCrCb);

    //Initializing the binary image with the same dimensions as original image
    bin_img = cv::Mat(orig_img.rows, orig_img.cols, CV_8U, cv::Scalar(0));

    double value[3];

    //Step 1: initializing with one gaussian for the first time and keeping the no. of models as 1
    cv::Vec3f val;
    uchar* r_ptr;
    uchar* b_ptr;
    for(int asg=0; asg<orig_img.rows; asg++ )
    {
        r_ptr = orig_img.ptr(asg);
        for(int asf=0; asf<orig_img.cols; asf++ )
        {

            gmm.N_ptr = gmm.Create_Node(*r_ptr,*(r_ptr+1),*(r_ptr+2));
            if( gmm.N_ptr != NULL ){
                gmm.N_ptr->pixel_s->weight = 1.0;
                gmm.Insert_End_Node(gmm.N_ptr);
            }
            else
            {
                std::cout << "Memory limit reached... ";
                waitKey(0);
                exit(0);
            }
        }
    }

    capture.read(orig_img);

    int nL,nC;

    if(orig_img.isContinuous() == true)
    {
        nL = 1;
        nC = orig_img.rows*orig_img.cols*orig_img.channels();
    }

    else
    {
        nL = orig_img.rows;
        nC = orig_img.cols*orig_img.channels();
    }

    double del[3], mal_dist;
    double sum = 0.0;
    double sum1 = 0.0;
    int count = 0;
    bool close = false;
    int background;
    double mult;
    double duration,duration1,duration2,duration3;
    double temp_cov = 0.0;
    double weight = 0.0;
    double var = 0.0;
    double muR,muG,muB,dR,dG,dB,rVal,gVal,bVal;

    //Step 2: Modelling each pixel with Gaussian
    duration1 = static_cast<double>(cv::getTickCount());
    bin_img = cv::Mat(orig_img.rows,orig_img.cols,CV_8UC1,cv::Scalar(0));

    while(!stop){
        duration3 = 0.0;
        if(!capture.read(orig_img)){
            stop = true;
            break;
        }
        int count = 0;

        gmm.N_ptr = gmm.N_start;
        duration = static_cast<double>(cv::getTickCount());
        for( i=0; i<nL; i++)
        {
            r_ptr = orig_img.ptr(i);
            b_ptr = bin_img.ptr(i);
            for( j=0; j<nC; j+=3)
            {
                sum = 0.0;
                sum1 = 0.0;
                close = false;
                background = 0;


                rVal = *(r_ptr++);
                gVal = *(r_ptr++);
                bVal = *(r_ptr++);

                gmm.start_gmm = gmm.N_ptr->pixel_s;
                gmm.rear = gmm.N_ptr->pixel_r;
                gmm.ptr = gmm.start_gmm;

                gmm.temp_ptr = NULL;

                if(gmm.N_ptr->no_of_components > 4)
                {
                    gmm.Delete_gaussian(gmm.rear);
                    gmm.N_ptr->no_of_components--;
                }

                for( k=0; k<gmm.N_ptr->no_of_components; k++ )
                {


                    weight = gmm.ptr->weight;
                    mult = alpha/weight;
                    weight = weight*gmm.alpha_bar + gmm.prune;
                    if(close == false)
                    {
                        muR = gmm.ptr->mean[0];
                        muG = gmm.ptr->mean[1];
                        muB = gmm.ptr->mean[2];

                        dR = rVal - muR;
                        dG = gVal - muG;
                        dB = bVal - muB;

                        var = gmm.ptr->covariance;
                        mal_dist = (dR*dR + dG*dG + dB*dB);

                        if((sum < gmm.cfbar) && (mal_dist < 16.0*var*var))
                            background = 255;

                        if( mal_dist < 9.0*var*var)
                        {
                            weight += alpha;
                            close = true;

                            gmm.ptr->mean[0] = muR + mult*dR;
                            gmm.ptr->mean[1] = muG + mult*dG;
                            gmm.ptr->mean[2] = muB + mult*dB;

                            temp_cov = var + mult*(mal_dist - var);
                            gmm.ptr->covariance = temp_cov<5.0?5.0:(temp_cov>20.0?20.0:temp_cov);
                            gmm.temp_ptr = gmm.ptr;
                        }
                    }

                    if(weight < -gmm.prune)
                    {
                        gmm.ptr = gmm.Delete_gaussian(gmm.ptr);
                        weight = 0;
                        gmm.N_ptr->no_of_components--;
                    }
                    else
                    {
                        sum += weight;
                        gmm.ptr->weight = weight;
                    }

                    gmm.ptr = gmm.ptr->Next;
                }

                if( close == false )
                {
                    gmm.ptr = new GMM::gaussian;
                    gmm.ptr->weight = alpha;
                    gmm.ptr->mean[0] = rVal;
                    gmm.ptr->mean[1] = gVal;
                    gmm.ptr->mean[2] = bVal;
                    gmm.ptr->covariance = covariance0;
                    gmm.ptr->Next = NULL;
                    gmm.ptr->Previous = NULL;
                    if(gmm.start_gmm == NULL)
                        gmm.start_gmm = gmm.rear = NULL;
                    else
                    {
                        gmm.ptr->Previous = gmm.rear;
                        gmm.rear->Next = gmm.ptr;
                        gmm.rear = gmm.ptr;
                    }
                    gmm.temp_ptr = gmm.ptr;
                    gmm.N_ptr->no_of_components++;
                }

                gmm.ptr = gmm.start_gmm;
                while( gmm.ptr != NULL)
                {
                    gmm.ptr->weight /= sum;
                    gmm.ptr = gmm.ptr->Next;
                }

                while(gmm.temp_ptr != NULL && gmm.temp_ptr->Previous != NULL)
                {
                    if(gmm.temp_ptr->weight <= gmm.temp_ptr->Previous->weight)
                        break;
                    else
                    {
                        gmm.next = gmm.temp_ptr->Next;
                        gmm.previous = gmm.temp_ptr->Previous;
                        if(gmm.start_gmm == gmm.previous)
                            gmm.start_gmm = gmm.temp_ptr;
                        gmm.previous->Next = gmm.next;
                        gmm.temp_ptr->Previous = gmm.previous->Previous;
                        gmm.temp_ptr->Next = gmm.previous;
                        if(gmm.previous->Previous != NULL)
                            gmm.previous->Previous->Next = gmm.temp_ptr;
                        if(gmm.next != NULL)
                            gmm.next->Previous = gmm.previous;
                        else
                            gmm.rear = gmm.previous;
                        gmm.previous->Previous = gmm.temp_ptr;
                    }

                    gmm.temp_ptr = gmm.temp_ptr->Previous;
                }

                gmm.N_ptr->pixel_s = gmm.start_gmm;
                gmm.N_ptr->pixel_r = gmm.rear;
                *b_ptr++ = background;
                gmm.N_ptr = gmm.N_ptr->Next;
            }
        }

        duration = static_cast<double>(cv::getTickCount())-duration;
        duration /= cv::getTickFrequency();

        std::cout << "\n duration :" << duration;
        std::cout << "\n counts : " << count;

        cv::cvtColor(orig_img, RGBframe, CV_BGR2RGB);
        img = QImage((const unsigned char*)(RGBframe.data),
                     RGBframe.cols,RGBframe.rows,QImage::Format_RGB888);

        int w=bin_img.cols;
        int h=bin_img.rows;
        img_gmm = QImage(w,h,QImage::Format_RGB32);
        QRgb pixel;
        Mat im;
        normalize(bin_img.clone(),im,0.0,255.0,CV_MINMAX,CV_8UC1);
        for(int i=0;i<w;i++)
        {
            for(int j=0;j<h;j++)
            {
                int gray = (int)im.at<unsigned char>(j, i);
                pixel = qRgb(gray,gray,gray);
                img_gmm.setPixel(i,j,pixel);
            }
        }
        emit processedImage(img,img_gmm, video);
        this->msleep(delay);
    }

    duration1 = static_cast<double>(cv::getTickCount())-duration1;
    duration1 /= cv::getTickFrequency();
    std::cout << "\n duration1 :" << duration1;
}
