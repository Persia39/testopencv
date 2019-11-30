#include "changer.h"
#include "ui_changer.h"

Changer::Changer(cv::Mat img) :
    ui(new Ui::Changer),now_degrees(0),src(img),mov_left_part(0),mov_right_part(0),now_degrees_y(0),
    mov_up(0),mov_bot(0)
{
    ui->setupUi(this);
}

Changer::~Changer()
{
    delete ui;
}

void Changer::getLeftImage(int rotation)
{
    qDebug()<<"Left grad do"<<now_degrees;
    using namespace cv;
    if(now_degrees-rotation>-23)
    {
        Mat left_image=Mat::zeros( src.rows, src.cols, src.type() );
        mov_left_part-=26*rotation;
        mov_right_part-=10*rotation;
        if(now_degrees-rotation>0)
        {
        std::vector <Point2f> ptr1;
        ptr1.push_back(Point2f(mov_left_part,0.f+mov_left_part/2));
        ptr1.push_back(Point2f(848.f,0.f));
        ptr1.push_back(Point2f(mov_left_part, 800.f-mov_left_part/2));
        ptr1.push_back(Point2f(848.f, 800.f));

        std::vector <Point2f> ptr2;
        ptr2.push_back(Point2f(0.f,0.f));
        ptr2.push_back(Point2f(848.f,mov_right_part));
        ptr2.push_back(Point2f(0, 800.f));
        ptr2.push_back(Point2f(848.f, 800.f-mov_right_part));
        Mat m=findHomography(ptr1,ptr2);
        warpPerspective(src,left_image,m,src.size());
        now_degrees-=rotation;
        emit sendRight(left_image);
    }
        else{
        std::vector <Point2f> ptr1;
        ptr1.push_back(Point2f(0,0.f));
        ptr1.push_back(Point2f(848.f+mov_left_part,-mov_left_part/2));
        ptr1.push_back(Point2f(0, 800.f));
        ptr1.push_back(Point2f(848.f+mov_left_part, 800.f+mov_left_part/2));

        std::vector <Point2f> ptr2;
        ptr2.push_back(Point2f(0.f,-mov_right_part));
        ptr2.push_back(Point2f(848.f,0));
        ptr2.push_back(Point2f(0, 800.f+mov_right_part));
        ptr2.push_back(Point2f(848.f, 800.f));
        Mat m=findHomography(ptr1,ptr2);
        warpPerspective(src,left_image,m,src.size());
        now_degrees-=rotation;
        emit sendRight(left_image);
        }
    }
    qDebug()<<"Left grad posle"<<now_degrees;
}

void Changer::getRightImage(int rotation)
{
    qDebug()<<"Grad do"<<now_degrees;
    using namespace cv;

    if(now_degrees+rotation<23)
    {
        mov_left_part+=26*rotation;
        mov_right_part+=10*rotation;
        Mat right_image=Mat::zeros( src.rows, src.cols, src.type() );
        if(now_degrees+rotation<0)
        {
            std::vector <Point2f> ptr1;
            ptr1.push_back(Point2f(0,0.f));
            ptr1.push_back(Point2f(848.f+mov_left_part,-mov_left_part/2));
            ptr1.push_back(Point2f(0, 800.f));
            ptr1.push_back(Point2f(874.f+mov_left_part, 800.f+mov_left_part/2));

            std::vector <Point2f> ptr2;
            ptr2.push_back(Point2f(0.f,-mov_right_part));
            ptr2.push_back(Point2f(848.f,0));
            ptr2.push_back(Point2f(0, 800.f+mov_right_part));
            ptr2.push_back(Point2f(848.f, 800.f));
            Mat m=findHomography(ptr1,ptr2);
            warpPerspective(src,right_image,m,src.size());
            now_degrees+=rotation;
            emit sendRight(right_image);
        }
        else
        {
            std::vector <Point2f> ptr1;
            ptr1.push_back(Point2f(mov_left_part,0.f+mov_left_part/2));
            ptr1.push_back(Point2f(848.f,0.f));
            ptr1.push_back(Point2f(mov_left_part, 800.f-mov_left_part/2));
            ptr1.push_back(Point2f(848.f, 800.f));

            std::vector <Point2f> ptr2;
            ptr2.push_back(Point2f(0.f,0.f));
            ptr2.push_back(Point2f(848.f,mov_right_part));
            ptr2.push_back(Point2f(0, 800.f));
            ptr2.push_back(Point2f(848.f, 800.f-mov_right_part));
            Mat m=findHomography(ptr1,ptr2);
            warpPerspective(src,right_image,m,src.size());
            now_degrees+=rotation;
            emit sendRight(right_image);
        }
    }
    qDebug()<<"Grad posle"<<now_degrees;
}

void Changer::getBottomImage(int rotation_y)
{
    using namespace cv;
    if(now_degrees_y-rotation_y>-21)
    {
        Mat bottom_image=Mat::zeros( src.rows, src.cols, src.type() );
        if(now_degrees_y>0)
        {
            now_degrees_y-=rotation_y;
            mov_up-=26*rotation_y;
            mov_bot-=10*rotation_y;
            std::vector <Point2f> ptr1;
            ptr1.push_back(Point2f(0.f,0.f));
            ptr1.push_back(Point2f(848.f,0.f));
            ptr1.push_back(Point2f(mov_up/2, 800.f-mov_up));
            ptr1.push_back(Point2f(848.f-mov_up/2, 800.f-mov_up));

            std::vector <Point2f> ptr2;
            ptr2.push_back(Point2f(mov_bot,0.f));
            ptr2.push_back(Point2f(848.f-mov_bot,0));
            ptr2.push_back(Point2f(0, 800.f));
            ptr2.push_back(Point2f(848.f, 800.f));
            Mat m=findHomography(ptr1,ptr2);
            warpPerspective(src,bottom_image,m,src.size());
        }
        else
        {
            std::vector <Point2f> ptr1;
            ptr1.push_back(Point2f(mov_up/2,mov_up));
            ptr1.push_back(Point2f(848.f-mov_up/2,mov_up));
            ptr1.push_back(Point2f(0.f, 800.f));
            ptr1.push_back(Point2f(848.f, 800.f));

            std::vector <Point2f> ptr2;
            ptr2.push_back(Point2f(0.f,0.f));
            ptr2.push_back(Point2f(848.f,0));
            ptr2.push_back(Point2f(mov_bot, 800.f));
            ptr2.push_back(Point2f(848.f-mov_bot, 800.f));
            Mat m=findHomography(ptr1,ptr2);
            warpPerspective(src,bottom_image,m,src.size());
            now_degrees_y-=rotation_y;
            mov_up+=26*rotation_y;
            mov_bot+=5*rotation_y;
        }
        emit sendUp(bottom_image);
    }
}

void Changer::getUpImage(int rotation_y)
{
    qDebug()<<"Degrees Y"<<now_degrees_y;
    using namespace cv;
    if(now_degrees_y+rotation_y<21)
    {
        Mat up_image=Mat::zeros( src.rows, src.cols, src.type() );
        if(now_degrees_y+rotation_y>=0)
        {
            now_degrees_y+=rotation_y;
            mov_up+=26*rotation_y;
            mov_bot+=10*rotation_y;
            std::vector <Point2f> ptr1;
            ptr1.push_back(Point2f(0.f,0.f));
            ptr1.push_back(Point2f(848.f,0.f));
            ptr1.push_back(Point2f(mov_up/2, 800.f-mov_up));
            ptr1.push_back(Point2f(848.f-mov_up/2, 800.f-mov_up));

            std::vector <Point2f> ptr2;
            ptr2.push_back(Point2f(mov_bot,0.f));
            ptr2.push_back(Point2f(848.f-mov_bot,0));
            ptr2.push_back(Point2f(0, 800.f));
            ptr2.push_back(Point2f(848.f, 800.f));
            Mat m=findHomography(ptr1,ptr2);
            warpPerspective(src,up_image,m,src.size());
        }
        else
        {
            now_degrees_y+=rotation_y;
            mov_up-=26*rotation_y;
            mov_bot-=10*rotation_y;
            std::vector <Point2f> ptr1;
            ptr1.push_back(Point2f(mov_up/2,mov_up));
            ptr1.push_back(Point2f(848.f-mov_up/2,mov_up));
            ptr1.push_back(Point2f(0.f, 800.f));
            ptr1.push_back(Point2f(848.f, 800.f));

            std::vector <Point2f> ptr2;
            ptr2.push_back(Point2f(0.f,0.f));
            ptr2.push_back(Point2f(848.f,0));
            ptr2.push_back(Point2f(mov_bot, 800.f));
            ptr2.push_back(Point2f(848.f-mov_bot, 800.f));
            Mat m=findHomography(ptr1,ptr2);
            warpPerspective(src,up_image,m,src.size());
        }
        emit sendUp(up_image);
    }
}
