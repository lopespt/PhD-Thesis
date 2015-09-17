#include "QImageCV.hpp"
#include <opencv2/opencv.hpp>
#include <Utilities/cvmatandqimage.h>
const cv::Mat &QImageCV::getCvBGRImage() const {
    if (bgrImage.empty()) {
        //cv::Mat ret(newImg.height(), newImg.width(), CV_8UC4, (uchar *) newImg.bits(), (size_t) newImg.bytesPerLine());
        //this->bgrImage = ret.clone();
        this->bgrImage = QtOcv::image2Mat_shared(*this);
        //cv::namedWindow("teste");
        //cv::imshow("teste", this->bgrImage);
        //cv::waitKey(0);
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

