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
    explicit Changer(QWidget *parent = nullptr,cv::Mat img={});
    ~Changer();

private:
    Ui::Changer *ui;
    int now_degrees,mov_left_part,mov_right_part,now_degrees_y,mov_up,mov_bot;
    double pixel_in_degree;
    cv:: Mat src;
signals:
    void sendLeft(cv::Mat);
    void sendRight(cv::Mat);
    void sendBottom(cv::Mat);
    void sendUp(cv::Mat);
public slots:
    void getLeftImage(int);
    void getRightImage(int);
    void getBottomImage(int);
    void getUpImage(int);
};

#endif // CHANGER_H
