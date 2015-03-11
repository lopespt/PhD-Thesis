#include "SegmentedImage.hpp"
#include <opencv/highgui.h>
#include <Utilities/Utils.hpp>

SegmentedImage::SegmentedImage(QImageCV img, QVector<Region> regions):
    image(img),
    regions(regions)
{
    for(Region& r:this->regions){
        r.setImage(&image);
    }

    /*for(Region& r:this->regions){
        printf("%d\n", r.getImage()->size().width());
    }*/
}


const QImageCV &SegmentedImage::getImage() const{
    return image;
}


const QVector<Region>& SegmentedImage::getRegions() const{
    return regions;
}

void SegmentedImage::showRegion(int i) const{
    Mat orig = Utils::QImage2Mat(image);
    Mat m(orig.size(), CV_8UC4, cvScalarAll(0));
    orig.copyTo( m , regions[i].getMask());
    imshow("img", m);
    waitKey(0);
}

SegmentedImage::~SegmentedImage()
{

}

