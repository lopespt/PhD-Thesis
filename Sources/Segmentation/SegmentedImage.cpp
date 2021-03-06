#include "SegmentedImage.hpp"
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

SegmentedImage::SegmentedImage(QImageCV img, QList<Region> regions) :
        image(img),
        regions(regions) {


    for (Region &r:this->regions) {
        r.setImage(&this->image);
    }

}

SegmentedImage::SegmentedImage(const SegmentedImage &other) :
        image(other.image),
        regions(other.regions) {
    for (Region &r:this->regions) {
        r.setImage(&this->image);
    }
}

const QImageCV &SegmentedImage::getImage() const {
    return image;
}


void SegmentedImage::showRegion(int i) const {
    Mat orig = QtOcv::image2Mat(image);
    Mat m(orig.size(), CV_8UC4, cvScalarAll(0));
    orig.copyTo(m, regions[i].getMask());
    //cv::resize(m, m, cv::Size(), 100, 100);
    cv::resize(m, m, cv::Size(300, 300));
    namedWindow("img", WINDOW_NORMAL);
    cv::imshow("img", m);
    waitKey(0);

}

const QList<Region> &SegmentedImage::getRegions() const {
    return this->regions;
}

SegmentedImage::~SegmentedImage() {

}

SegmentedImage::SegmentedImage(const SupervisedImage &img) : image(*img.getImage()), regions(img.getRegions()) {

}
