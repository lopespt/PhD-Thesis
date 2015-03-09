#include "VoronoiRandomSegmenter.hpp"
#include <opencv/cv.h>
#include <Utilities/VoronoiDiagramGenerator.hpp>

using namespace cv;
using namespace Voronoi;
VoronoiRandomSegmenter::VoronoiRandomSegmenter()
{
    srand(time(0));
}

VoronoiRandomSegmenter::~VoronoiRandomSegmenter()
{

}

void VoronoiRandomSegmenter::setNumberOfRegions(int regions){
    this->regions = regions;
}

SegmentedImage VoronoiRandomSegmenter::getNextSegmentation(const QImage &image) const{
    Mat img = Utils::QImage2Mat(image);

    Mat m(img.size(), CV_8UC1, cvScalarAll(0));

    VoronoiDiagramGenerator v;
    vector<float> x;
    vector<float> y;
    for(int i=0; i < regions; i++){
        x.push_back(rand() % img.size().width);
        y.push_back(rand() % img.size().height);
    }

    v.generateVoronoi(x.data(), y.data(), regions, -100, image.width()+100, -100, image.height()+100);

    float px, py, p2x, p2y;
    v.resetIterator();
    //rectangle(m, cv::Point(0,0), cv::Point(399,399),cvScalarAll(255));
    while(v.getNext(px,py,p2x,p2y)){
        line(m,cv::Point(px,py), cv::Point(p2x,p2y), cvScalarAll(255), 1);
        //printf("%f %f %f %f\n", px, py, p2x, p2y);
    }
    Mat vor = m.clone();
    QVector<Region> regions;


    for(unsigned int i=0;i<this->regions;i++){
        m = vor.clone();
        floodFill(m,cv::Point(x[i],y[i]), cvScalarAll(255));
        erode(m,m, getStructuringElement(MORPH_ERODE, cv::Size(3,3)));
        dilate(m,m, getStructuringElement(MORPH_DILATE, cv::Size(3,3)));
        regions.append(Region(NULL,m));
    }

    return SegmentedImage(image, regions);
}

QList<SegmentedImage> VoronoiRandomSegmenter::execute(const QImage &img, int nSegmentations){
    QList<SegmentedImage> res;
    for(int i=0;i<nSegmentations;i++){
        res.append(getNextSegmentation(img));
    }
    return res;
}
