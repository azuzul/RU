#include "gmm.h"

GMM::GMM(double alpha, double cT, double covariance0, double cf)
{
    this->alpha = alpha;
    this->cT = cT;
    this->covariance0 = covariance0;
    this->cf = cf;
    this->cfbar = 1.0-cf;
    this->temp_thr = 9.0*covariance0*covariance0;
    this->prune = -alpha*cT;
    this->alpha_bar = 1.0-alpha;
}

GMM::Node* GMM::Create_Node(double info1, double info2, double info3)
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

GMM::gaussian* GMM::Create_gaussian(double info1, double info2, double info3)
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

void GMM::Insert_End_Node(Node* np)
{
    if( N_start != NULL )
    {
        N_rear->Next = np;
        N_rear = np;
    }
    else
        N_start = N_rear = np;
}

void GMM::Insert_End_gaussian(GMM::gaussian* nptr)
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

GMM::gaussian* GMM::Delete_gaussian(GMM::gaussian* nptr)
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
        exit(0);
    }
    return nptr;
}
