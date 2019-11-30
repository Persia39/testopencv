#include "manager.h"
#include "ui_manager.h"

Manager::Manager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Manager),state(0)
{
    ui->setupUi(this);
    src = cv::imread("E:/programs/QTprojects/teskCV/debug/corid.png");
    chang=new Changer(src);
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
    connect(this,&Manager::setUpImage,chang,&Changer::getUpImage);
    connect(chang,&Changer::sendUp,this,&Manager::get_images);
    connect(this,&Manager::setBottomImage,chang,&Changer::getBottomImage);
    connect(chang,&Changer::sendBottom,this,&Manager::get_images);
    //1pixel=0,036 degrees/ camera=45 degrees, 1 degree=26 pixel

    mov_y=0;
    mov_x=0;
    src1=cv::Mat::zeros( src.rows, src.cols, src.type() );
    now_degrees=0;
    now_degrees_y=0;
    mov_up=0;
    mov_bot=0;
}

Manager::~Manager()
{
    delete chang;
    delete ui;
}

void Manager::on_button_open_clicked()
{
    emit setBottomImage(ui->degree->text().toInt());
}

void Manager::on_left_button_clicked()
{
    emit setLeftImage(ui->degree->text().toInt());
}

void Manager::get_images(cv::Mat newimg)
{
    ui->image_label->setPixmap(QPixmap::fromImage(QImage(newimg.data, newimg.cols, newimg.rows, newimg.step, QImage::Format_RGB888)));
}

void Manager::on_right_button_clicked()
{
    emit setRightImage(ui->degree->text().toInt());
}

void Manager::on_up_button_clicked()
{
    emit setUpImage(ui->degree->text().toInt());
}

void Manager::on_pushButton_clicked()
{
    using namespace cv;


}

void Manager::on_pushButton_2_clicked()
{
    using namespace cv;
    std::vector <Point2f> ptr1;
    ptr1.push_back(Point2f(mov_y,0.f+mov_y/2));
    ptr1.push_back(Point2f(848.f,0.f));
    ptr1.push_back(Point2f(mov_y+mov_up/2, 800.f-mov_y/2 -mov_up));
    ptr1.push_back(Point2f(848.f-mov_up/2, 800.f-mov_up));

    std::vector <Point2f> ptr2;
    ptr2.push_back(Point2f(0.f,0.f));
    ptr2.push_back(Point2f(848.f,mov_x));
    ptr2.push_back(Point2f(mov_bot, 800.f));
    ptr2.push_back(Point2f(848.f-mov_bot, 800.f-mov_x));
    Mat m=findHomography(ptr1,ptr2);
    warpPerspective(src,src1,m,src.size());
    now_degrees_y+=(ui->degree->text().toInt());
    mov_up+=26*(ui->degree->text().toInt());
    mov_bot+=10*(ui->degree->text().toInt());
    cv::imshow("teri",src1);
}
