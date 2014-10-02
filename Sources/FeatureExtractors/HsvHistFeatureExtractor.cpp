
#include "HsvHistFeatureExtractor.hpp"
#include <opencv/cv.h>

HsvHistFeatureExtractor::HsvHistFeatureExtractor(){
}

QVector<float> HsvHistFeatureExtractor::doExtraction(Region* region, int discretization){
    QVector<float> vect(1);

//    cv::calcHist

    return vect;
}


const char* HsvHistFeatureExtractor::getFeatureName(){
    return "AreaFeature";
}

