#include "VoronoiRandomSegmenter.hpp"
#include <opencv/cv.h>
using namespace cv;
VoronoiRandomSegmenter::VoronoiRandomSegmenter()
{

}

VoronoiRandomSegmenter::~VoronoiRandomSegmenter()
{

}

SegmentedImage VoronoiRandomSegmenter::execute(const cv::Mat &img){
    /*
    Mat m(img.size, CV_8UC1, cvScalarAll(0));

    VoronoiDiagramGenerator v;
    float x[] = {2,8,300,10, 15};
    float y[] = {5,5,25,40,200};

    v.generateVoronoi(x,y,5,-100,500,-100,500);

    float px, py, p2x, p2y;
    printf("entrando no while\n");
    v.resetIterator();
    //rectangle(m, cv::Point(0,0), cv::Point(399,399),cvScalarAll(255));
    while(v.getNext(px,py,p2x,p2y)){
        line(m,cv::Point(px,py), cv::Point(p2x,p2y), cvScalarAll(255), 1);
        printf("%f %f %f %f\n", px, py, p2x, p2y);
    }
    Mat vor = m.clone();
    for(int i=0;i<5;i++){
        m = vor.clone();
        floodFill(m,cv::Point(x[i],y[i]), cvScalarAll(255));
        erode(m,m, getStructuringElement(MORPH_ERODE, cv::Size(3,3)));
        dilate(m,m, getStructuringElement(MORPH_DILATE, cv::Size(3,3)));
        imshow("win", m);
        waitKey();
    }
    fflush(stdout);
*/
return SegmentedImage();
}
