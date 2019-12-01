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
    void get_images(cv::Mat);
    void on_right_button_clicked();
    void on_up_button_clicked();
signals:
    void setLeftImage(int);
    void setRightImage(int);
    void setBottomImage(int);
    void setUpImage(int);

private:
    Ui::Manager *ui;
    Changer* chang;
    cv::Mat src;
};

#endif // MANAGER_H
