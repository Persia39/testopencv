#include "manager.h"
#include "ui_manager.h"

Manager::Manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manager),state(0)
{
    ui->setupUi(this);
    chang=new Changer();
    src = cv::imread("E:/programs/QTprojects/teskCV/debug/corid.png");
    double mydata[3][3]={{283.3204, 0, 425.59799},{0, 284.35281, 403.94809},{0, 0, 1}};
    cv::Mat cameramatrix=cv::Mat(3,3, CV_64F, mydata);
    double D[14]={-0.001933632, 0.03497972, -0.032952748, 0.0049995692, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    cv::Mat dist=cv::Mat(1,14,CV_64F,D);
    double D1[4]={-0.001933632, 0.03497972, -0.032952748, 0.0049995692};
    cv::Mat dist1=cv::Mat(1,4,CV_64F,D1);
    cv::Mat newcameramatrix=getOptimalNewCameraMatrix(cameramatrix,dist,src.size(),1);
    cv::Mat mapx,mapy;
    cv::fisheye::initUndistortRectifyMap(cameramatrix,dist1,cv::Mat(),newcameramatrix,src.size(),CV_32FC1,mapx,mapy);
    remap(src,src,mapx,mapy,cv::INTER_LINEAR,cv::BORDER_CONSTANT);
    ui->image_label->setPixmap(QPixmap::fromImage(QImage(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888)));
    ui->image_label->setScaledContents( true );
    ui->image_label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    connect(this,&Manager::setLeftImage,chang,&Changer::getLeftImage);
    connect(chang,&Changer::sendLeft,this,&Manager::get_images);
    connect(this,&Manager::setRightImage,chang,&Changer::getRightImage);
    connect(chang,&Changer::sendRight,this,&Manager::get_images);
    connect(this,&Manager::setBottomImage,chang,&Changer::getBottomImage);
    connect(chang,&Changer::sendBottom,this,&Manager::get_images);
}

Manager::~Manager()
{
    delete chang;
    delete ui;
}

void Manager::on_button_open_clicked()
{
    if(state==0 && bottom_img.rows==0 && bottom_img.cols==0)
    {
        emit setBottomImage(src);
        state=3;
    }
    else if(state==0)
    {
        ui->image_label->setPixmap(QPixmap::fromImage(QImage(bottom_img.data, bottom_img.cols, bottom_img.rows, bottom_img.step, QImage::Format_RGB888)));
        state=3;
    }
}

void Manager::on_left_button_clicked()
{
    if(state==0 && left_img.rows==0 && left_img.cols==0)
    {
        emit setLeftImage(src);
        state=1;
    }
    else if(state==0)
    {
        ui->image_label->setPixmap(QPixmap::fromImage(QImage(left_img.data, left_img.cols, left_img.rows, left_img.step, QImage::Format_RGB888)));
        state=1;
    }
    else if(state==2)
    {
        ui->image_label->setPixmap(QPixmap::fromImage(QImage(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888)));
        state=0;
    }
}

void Manager::get_images(cv::Mat newimg, int st)
{
    if(st==1)
        left_img=newimg;
    else if(st==2)
        right_img=newimg;
    else if(st==3)
        bottom_img=newimg;
    ui->image_label->setPixmap(QPixmap::fromImage(QImage(newimg.data, newimg.cols, newimg.rows, newimg.step, QImage::Format_RGB888)));
}

void Manager::on_right_button_clicked()
{
    if(state==0 && right_img.rows==0 && right_img.cols==0)
    {
        emit setRightImage(src);
        state=2;
    }
    else if(state==0)
    {
        ui->image_label->setPixmap(QPixmap::fromImage(QImage(right_img.data, right_img.cols, right_img.rows, right_img.step, QImage::Format_RGB888)));
        state=2;
    }
    else if(state==1)
    {
        ui->image_label->setPixmap(QPixmap::fromImage(QImage(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888)));
        state=0;
    }
}

void Manager::on_up_button_clicked()
{
    if(state==3)
    {
        ui->image_label->setPixmap(QPixmap::fromImage(QImage(src.data, src.cols, src.rows, src.step, QImage::Format_RGB888)));
        state=0;
    }
}
