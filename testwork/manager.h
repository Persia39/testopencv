#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include "changer.h"
#include <QDebug>
namespace Ui {
class Manager;
}

class Manager : public QWidget
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = nullptr);
    ~Manager();

private slots:
    void on_button_open_clicked();
    void on_left_button_clicked();
    void get_images(cv::Mat);

    void on_right_button_clicked();

    void on_up_button_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void setLeftImage(int);
    void setRightImage(int);
    void setBottomImage(int);
    void setUpImage(int);

private:
    Ui::Manager *ui;
    Changer* chang;
    uint state;
    cv::Mat src;
    cv::Mat left_img;
    cv::Mat right_img;
    cv::Mat bottom_img;

    int mov_x;
    int mov_y;
    cv::Mat src1;
    int now_degrees;
    int now_degrees_y;
    int mov_up;
    int mov_bot;
};

#endif // MANAGER_H
