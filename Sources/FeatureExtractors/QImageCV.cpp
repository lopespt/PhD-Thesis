#include "QImageCV.hpp"

const cv::Mat &QImageCV::getCvBGRImage() const {
    if (bgrImage.empty()) {
        const QImage &newImg = *this;
        cv::Mat ret(newImg.height(), newImg.width(), CV_8UC4, (uchar *) newImg.bits(), newImg.bytesPerLine());
        this->bgrImage = ret.clone();
    }
    return this->bgrImage;
}

const cv::Mat &QImageCV::getCvHsvImage() const {
    if (hsvImage.empty()) {
        hsvImage = getCvBGRImage().clone();
        cv::cvtColor(hsvImage, hsvImage, CV_BGR2HSV);
    }
    return this->hsvImage;
}

QImageCV::~QImageCV() {

}

