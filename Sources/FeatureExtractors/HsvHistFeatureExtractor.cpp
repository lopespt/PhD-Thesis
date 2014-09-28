
#include <HsvHistFeatureExtractor.hpp>
#include <opencv/cv.h>

HsvHistFeatureExtractor::HsvHistFeatureExtractor(){
}

QVector<float> HsvHistFeatureExtractor::doExtraction(Region* region){
    QVector<float> vect(1);

//    cv::calcHist

    return vect;
}

void HsvHistFeatureExtractor::doDiscretization(QVector<float> &feature, int discretization){
    for(int i=0;i<feature.size();i++){
        feature[i] = ((int)(feature[i] * discretization))/(float)discretization;
    }
}

const char* HsvHistFeatureExtractor::getFeatureName(){
    return "AreaFeature";
}

