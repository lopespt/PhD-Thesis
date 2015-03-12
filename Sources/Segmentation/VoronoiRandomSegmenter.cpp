#include "VoronoiRandomSegmenter.hpp"
#include <opencv/cv.h>
#include <Utilities/VoronoiDiagramGenerator.hpp>
#include <QList>
#include <opencv/highgui.h>

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

inline bool hasNeightboor(float a, const vector<float>& v){
    for(const float& f :  v){
        if(fabs(a - f) <= 3)
            return true;
    }
    return false;
}

SegmentedImage VoronoiRandomSegmenter::getNextSegmentation(const QImage &image) const{
    Mat img = Utils::QImage2Mat(image);

    Mat m(img.size(), CV_8UC1, cvScalarAll(0));

    VoronoiDiagramGenerator v;
    vector<float> x;
    vector<float> y;
    for(int i=0; i < regions; i++){
        
        float px;
        float py;
        //find valid values of px and py
        do{
            px= (rand() % img.size().width-3) + 3;
        }while( hasNeightboor(px, x));
        do{
            py = (rand() % img.size().height-3) + 3;
        }while( hasNeightboor(py, y));
               
        x.push_back( px );
        y.push_back( py );
    }

    v.generateVoronoi(x.data(), y.data(), regions, -10, image.width()+10, -10, image.height()+10);

    float px, py, p2x, p2y;
    v.resetIterator();
    //rectangle(m, cv::Point(0,0), cv::Point(399,399),cvScalarAll(255));
    while(v.getNext(px,py,p2x,p2y)){
        line(m,cv::Point(px,py), cv::Point(p2x,p2y), cvScalarAll(255), 1);
        //printf("%f %f %f %f\n", px, py, p2x, p2y);
    }
    Mat vor = m.clone();

    QList<Region> regions;


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
