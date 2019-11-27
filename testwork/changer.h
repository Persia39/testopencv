#ifndef CHANGER_H
#define CHANGER_H

#include <QWidget>
#include "opencv2/opencv.hpp"
namespace Ui {
class Changer;
}

class Changer : public QWidget
{
    Q_OBJECT

public:
    explicit Changer(QWidget *parent = nullptr);
    ~Changer();

private:
    Ui::Changer *ui;
signals:
    void sendLeft(cv::Mat,int);
    void sendRight(cv::Mat,int);
    void sendBottom(cv::Mat,int);
public slots:
    void getLeftImage(cv::Mat);
    void getRightImage(cv::Mat);
    void getBottomImage(cv::Mat);
};

#endif // CHANGER_H
