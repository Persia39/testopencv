#ifndef MANAGER_H
#define MANAGER_H

#include <QWidget>
#include "changer.h"

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
    void get_images(cv::Mat,int);

    void on_right_button_clicked();

    void on_up_button_clicked();

signals:
    void setLeftImage(cv::Mat);
    void setRightImage(cv::Mat);
    void setBottomImage(cv::Mat);

private:
    Ui::Manager *ui;
    Changer* chang;
    uint state;
    cv::Mat src;
    cv::Mat left_img;
    cv::Mat right_img;
    cv::Mat bottom_img;

};

#endif // MANAGER_H
