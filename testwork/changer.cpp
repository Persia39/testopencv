#include "changer.h"
#include "ui_changer.h"

Changer::Changer(QWidget *parent,cv::Mat img) :
    ui(new Ui::Changer),now_degrees(0),src(img),mov_left_part(0),mov_right_part(0),now_degrees_y(0),
    mov_up(0),mov_bot(0),pixel_in_degree(6.5)
{
    ui->setupUi(this);
    ui->label_degree_x->setText("0");
    ui->label_degree_y->setText("0");
}

Changer::~Changer()
{
    delete ui;
}

void Changer::getLeftImage(int rotation)
{
    using namespace cv;
    if(now_degrees-rotation>-91 && now_degrees_y==0)
    {
        ui->label_error->setText("");
        Mat left_image=Mat::zeros( src.rows, src.cols, src.type() );
        mov_left_part-=pixel_in_degree*rotation;
        mov_right_part-=2*rotation;
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
    else if(now_degrees_y!=0)
        ui->label_error->setText("Please make the angle Y equal to 0 degrees");
    ui->label_degree_x->setText(QString::number(now_degrees));
}

void Changer::getRightImage(int rotation)
{
    using namespace cv;

    if(now_degrees+rotation<91 && now_degrees_y==0)
    {
        ui->label_error->setText("");
        mov_left_part+=pixel_in_degree*rotation;
        mov_right_part+=2*rotation;
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
    else if(now_degrees_y!=0)
        ui->label_error->setText("Please make the angle Y equal to 0 degrees");
    ui->label_degree_x->setText(QString::number(now_degrees));
}

void Changer::getBottomImage(int rotation_y)
{
    using namespace cv;
    if(now_degrees_y-rotation_y>-91 && now_degrees==0)
    {
        ui->label_error->setText("");
        now_degrees_y-=rotation_y;
        mov_up-=pixel_in_degree*rotation_y;
        mov_bot-=2*rotation_y;
        Mat bottom_image=Mat::zeros( src.rows, src.cols, src.type() );
        if(now_degrees_y-rotation_y>=0)
        {
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
            ptr1.push_back(Point2f(-mov_up/2,-mov_up));
            ptr1.push_back(Point2f(848.f+mov_up/2,-mov_up));
            ptr1.push_back(Point2f(0.f, 800.f));
            ptr1.push_back(Point2f(848.f, 800.f));

            std::vector <Point2f> ptr2;
            ptr2.push_back(Point2f(0.f,0.f));
            ptr2.push_back(Point2f(848.f,0));
            ptr2.push_back(Point2f(-mov_bot, 800.f));
            ptr2.push_back(Point2f(848.f+mov_bot, 800.f));
            Mat m=findHomography(ptr1,ptr2);
            warpPerspective(src,bottom_image,m,src.size());
        }
        ui->label_degree_y->setText(QString::number(now_degrees_y));
        emit sendUp(bottom_image);
    }
    else if(now_degrees_y!=0)
        ui->label_error->setText("Please make the angle X equal to 0 degrees");
}

void Changer::getUpImage(int rotation_y)
{
    using namespace cv;
    if(now_degrees_y+rotation_y<91 && now_degrees==0)
    {
        ui->label_error->setText("");
        now_degrees_y+=rotation_y;
        mov_up+=pixel_in_degree*rotation_y;
        mov_bot+=2*rotation_y;
        Mat up_image=Mat::zeros( src.rows, src.cols, src.type() );
        if(now_degrees_y+rotation_y>0)
        {
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
            std::vector <Point2f> ptr1;
            ptr1.push_back(Point2f(-mov_up/2,-mov_up));
            ptr1.push_back(Point2f(848.f+mov_up/2,-mov_up));
            ptr1.push_back(Point2f(0.f, 800.f));
            ptr1.push_back(Point2f(848.f, 800.f));

            std::vector <Point2f> ptr2;
            ptr2.push_back(Point2f(0.f,0.f));
            ptr2.push_back(Point2f(848.f,0));
            ptr2.push_back(Point2f(-mov_bot, 800.f));
            ptr2.push_back(Point2f(848.f+mov_bot, 800.f));
            Mat m=findHomography(ptr1,ptr2);
            warpPerspective(src,up_image,m,src.size());
        }
        emit sendUp(up_image);
        ui->label_degree_y->setText(QString::number(now_degrees_y));
    }
    else if(now_degrees!=0)
    {
        ui->label_error->setText("Please make the angle X equal to 0 degrees");
    }
}
