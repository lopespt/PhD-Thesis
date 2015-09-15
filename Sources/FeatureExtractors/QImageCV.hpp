#ifndef QIMAGECV_HPP
#define QIMAGECV_HPP

#include <QImage>
#include <opencv/cv.h>
#include <Utilities/Utils.hpp>

class QImageCV : public QImage {
private:
    mutable cv::Mat hsvImage;
    mutable cv::Mat bgrImage;

public:

    QImageCV() : QImage() { }

    QImageCV(const QImageCV& other):hsvImage(other.hsvImage.clone()), bgrImage(other.bgrImage.clone()) {

    }

    QImageCV(const QImage &other) : QImage(other) {

    }
    QImageCV(const cv::Mat &other) : QImage( Utils::Mat2QImage(other.clone()) ) { }

    QImageCV(QString filename) : QImage(filename) { }

    const cv::Mat &getCvBGRImage() const;

    const cv::Mat &getCvHsvImage() const;

    void printf(char * format, ...){

    }

    ~QImageCV();
};

#endif // QIMAGECV_HPP
