#include "player.h"
#include <opencv2/features2d/features2d.hpp>
#include <vector>
#include <unistd.h>
#include <iostream>

Player::Node* Player::Create_Node(double info1, double info2, double info3)
{
    N_ptr = new Node;
    if(N_ptr != NULL)
    {
        N_ptr->Next = NULL;
        N_ptr->no_of_components = 1;
        N_ptr->pixel_s = N_ptr->pixel_r = Create_gaussian(info1,info2, info3);
    }
    return N_ptr;
}

Player::gaussian* Player::Create_gaussian(double info1, double info2, double info3)
{
    ptr = new gaussian;
    if(ptr != NULL)
    {
        ptr->mean[0] = info1;
        ptr->mean[1] = info2;
        ptr->mean[2] = info3;
        ptr->covariance = covariance0;
        ptr->weight = alpha;
        ptr->Next = NULL;
        ptr->Previous = NULL;
    }
    return ptr;
}

void Player::Insert_End_Node(Node* np)
{
    if( N_start != NULL )
    {
        N_rear->Next = np;
        N_rear = np;
    }
    else
        N_start = N_rear = np;
}

void Player::Insert_End_gaussian(Player::gaussian* nptr)
{
    if(start_gmm != NULL)
    {
        rear->Next = nptr;
        nptr->Previous = rear;
        rear = nptr;
    }
    else
        start_gmm = rear = nptr;
}

Player::gaussian* Player::Delete_gaussian(Player::gaussian* nptr)
{
    previous = nptr->Previous;
    next = nptr->Next;
    if(start_gmm != NULL)
    {
        if(nptr == start_gmm && nptr == rear)
        {
            start_gmm = rear = NULL;
            delete nptr;
        }
        else if(nptr == start_gmm)
        {
            next->Previous = NULL;
            start_gmm = next;
            delete nptr;
            nptr = start_gmm;
        }
        else if(nptr == rear)
        {
            previous->Next = NULL;
            rear = previous;
            delete nptr;
            nptr = rear;
        }
        else
        {
            previous->Next = next;
            next->Previous = previous;
            delete nptr;
            nptr = next;
        }
    }
    else
    {
        waitKey(0);
        exit(0);
    }
    return nptr;
}

Player::Player(QObject *parent,int video)
    : QThread(parent)
{
    stop = true;
    this->video=video;
}

bool Player::loadVideo(string filename){

    if(video == 0) {
        capture.open(0);
    } else {
        capture.open(filename);
    }
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
    frameRate = 30;
    int delay = (1000/frameRate);
    std::cout << frameRate << std::endl;
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

    frameRate = 30;
    int delay = (1000/frameRate);

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

            N_ptr = Create_Node(*r_ptr,*(r_ptr+1),*(r_ptr+2));
            if( N_ptr != NULL ){
                N_ptr->pixel_s->weight = 1.0;
                Insert_End_Node(N_ptr);
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

        N_ptr = N_start;
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

                start_gmm = N_ptr->pixel_s;
                rear = N_ptr->pixel_r;
                ptr = start_gmm;

                temp_ptr = NULL;

                if(N_ptr->no_of_components > 4)
                {
                    Delete_gaussian(rear);
                    N_ptr->no_of_components--;
                }

                for( k=0; k<N_ptr->no_of_components; k++ )
                {


                    weight = ptr->weight;
                    mult = alpha/weight;
                    weight = weight*alpha_bar + prune;
                    if(close == false)
                    {
                        muR = ptr->mean[0];
                        muG = ptr->mean[1];
                        muB = ptr->mean[2];

                        dR = rVal - muR;
                        dG = gVal - muG;
                        dB = bVal - muB;

                        var = ptr->covariance;
                        mal_dist = (dR*dR + dG*dG + dB*dB);

                        if((sum < cfbar) && (mal_dist < 16.0*var*var))
                            background = 255;

                        if( mal_dist < 9.0*var*var)
                        {
                            weight += alpha;
                            close = true;

                            ptr->mean[0] = muR + mult*dR;
                            ptr->mean[1] = muG + mult*dG;
                            ptr->mean[2] = muB + mult*dB;

                            temp_cov = var + mult*(mal_dist - var);
                            ptr->covariance = temp_cov<5.0?5.0:(temp_cov>20.0?20.0:temp_cov);
                            temp_ptr = ptr;
                        }
                    }

                    if(weight < -prune)
                    {
                        ptr = Delete_gaussian(ptr);
                        weight = 0;
                        N_ptr->no_of_components--;
                    }
                    else
                    {
                        sum += weight;
                        ptr->weight = weight;
                    }

                    ptr = ptr->Next;
                }

                if( close == false )
                {
                    ptr = new gaussian;
                    ptr->weight = alpha;
                    ptr->mean[0] = rVal;
                    ptr->mean[1] = gVal;
                    ptr->mean[2] = bVal;
                    ptr->covariance = covariance0;
                    ptr->Next = NULL;
                    ptr->Previous = NULL;
                    if(start_gmm == NULL)
                        start_gmm = rear = NULL;
                    else
                    {
                        ptr->Previous = rear;
                        rear->Next = ptr;
                        rear = ptr;
                    }
                    temp_ptr = ptr;
                    N_ptr->no_of_components++;
                }

                ptr = start_gmm;
                while( ptr != NULL)
                {
                    ptr->weight /= sum;
                    ptr = ptr->Next;
                }

                while(temp_ptr != NULL && temp_ptr->Previous != NULL)
                {
                    if(temp_ptr->weight <= temp_ptr->Previous->weight)
                        break;
                    else
                    {
                        next = temp_ptr->Next;
                        previous = temp_ptr->Previous;
                        if(start_gmm == previous)
                            start_gmm = temp_ptr;
                        previous->Next = next;
                        temp_ptr->Previous = previous->Previous;
                        temp_ptr->Next = previous;
                        if(previous->Previous != NULL)
                            previous->Previous->Next = temp_ptr;
                        if(next != NULL)
                            next->Previous = previous;
                        else
                            rear = previous;
                        previous->Previous = temp_ptr;
                    }

                    temp_ptr = temp_ptr->Previous;
                }

                N_ptr->pixel_s = start_gmm;
                N_ptr->pixel_r = rear;
                *b_ptr++ = background;
                N_ptr = N_ptr->Next;
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
