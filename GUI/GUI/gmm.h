#ifndef GMM_H
#define GMM_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cstdlib>

class GMM
{       
public:
    //Some constants for the algorithm
    const double pi = 3.142;
    double alpha;
    double cT;
    double covariance0;
    double cf;
    double cfbar;
    double temp_thr;
    double prune;
    double alpha_bar;
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

    //Some function associated with the structure management
    Node* Create_Node(double info1, double info2, double info3);
    void Insert_End_Node(Node* np);
    gaussian* Create_gaussian(double info1, double info2, double info3);
    void Insert_End_gaussian(gaussian* nptr);
    gaussian* Delete_gaussian(gaussian* nptr);

    GMM(double alpha = 0.002, double cT = 0.05, double covariance0 = 11.0, double cf = 0.1);
};

#endif // GMM_H
