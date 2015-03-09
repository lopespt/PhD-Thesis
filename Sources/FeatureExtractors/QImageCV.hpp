#ifndef QIMAGECV_HPP
#define QIMAGECV_HPP

#include <QImage>
#include <opencv/cv.h>
class QImageCV: public QImage
{
private:
    mutable cv::Mat hsvImage;
    mutable cv::Mat bgrImage;
public:

    QImageCV():QImage(){}
    QImageCV(const QImage& other):QImage(other){}
    QImageCV(QString filename):QImage(filename){}

    cv::Mat getCvBGRImage() const;
    cv::Mat getCvHsvImage() const;

    ~QImageCV();
};

#endif // QIMAGECV_HPP
