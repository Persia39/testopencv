#include "changer.h"
#include "ui_changer.h"

Changer::Changer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Changer)
{
    ui->setupUi(this);
}

Changer::~Changer()
{
    delete ui;
}

void Changer::getLeftImage(cv::Mat newimg)
{
    using namespace cv;
    std::vector <Point2f> ptr1;
    ptr1.push_back(Point2f(0.f,425.f));
    ptr1.push_back(Point2f(393.f,425.f));
    ptr1.push_back(Point2f(0.f, 790.f));
    ptr1.push_back(Point2f(393.f, 470.f));

    std::vector <Point2f> ptr2;
    ptr2.push_back(Point2f(0.f,400.f));
    ptr2.push_back(Point2f(846.f,300.f));
    ptr2.push_back(Point2f(0.f,600.f));
    ptr2.push_back(Point2f(846,400.f));
    Mat m=findHomography(ptr1,ptr2);

    Mat left_image=Mat::zeros( newimg.rows, newimg.cols, newimg.type() );
    warpPerspective(newimg,left_image,m,newimg.size());
    emit sendLeft(left_image,1);
}

void Changer::getRightImage(cv::Mat newimg)
{
    using namespace cv;
    std::vector <Point2f> ptr1;
    ptr1.push_back(Point2f(521.f,300.f));
    ptr1.push_back(Point2f(846.f,300.f));
    ptr1.push_back(Point2f(521.f, 514.f));
    ptr1.push_back(Point2f(846.f, 790.f));

    std::vector <Point2f> ptr2;
    ptr2.push_back(Point2f(0.f,0.f));
    ptr2.push_back(Point2f(846.f,250.f));
    ptr2.push_back(Point2f(0.f,790.f));
    ptr2.push_back(Point2f(846,500.f));
    Mat m=findHomography(ptr1,ptr2);

    Mat right_image=Mat::zeros( newimg.rows, newimg.cols, newimg.type() );
    warpPerspective(newimg,right_image,m,newimg.size());
    emit sendRight(right_image,2);
}

void Changer::getBottomImage(cv::Mat newimg)
{
    using namespace cv;
    std::vector <Point2f> ptr1;
    ptr1.push_back(Point2f(336.f,470.f));
    ptr1.push_back(Point2f(542.f,470.f));
    ptr1.push_back(Point2f(124.f, 785.f));
    ptr1.push_back(Point2f(713.f, 794.f));

    std::vector <Point2f> ptr2;
    ptr2.push_back(Point2f(0.f,0.f));
    ptr2.push_back(Point2f(846.f,0.f));
    ptr2.push_back(Point2f(0.f,794.f));
    ptr2.push_back(Point2f(846,794.f));
    Mat m=findHomography(ptr1,ptr2);

    Mat bottom_image=Mat::zeros( newimg.rows, newimg.cols, newimg.type() );
    warpPerspective(newimg,bottom_image,m,newimg.size());
    emit sendLeft(bottom_image,3);
}
