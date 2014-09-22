
#include "AreaFeatureExtractor.hpp"

AreaFeatureExtractor::AreaFeatureExtractor(){
}

QVector<float> AreaFeatureExtractor::doExtraction(Region* region){
    QVector<float> vect(1);
    float area = 0;
    bool ok;
    for(int i=0;i<region->getBoundaryRect().width();i++){
        for(int j=0;j<region->getBoundaryRect().height();j++){
           region->getPixelRelative(i,j, &ok); 
           if(ok)
               area++;
        }
    }
    vect[0] = area / (region->getBoundaryRect().width() * region->getBoundaryRect().height());
    return vect;
}

void AreaFeatureExtractor::doDiscretization(QVector<float> &feature, int discretization){
    for(int i=0;i<feature.size();i++){
        feature[i] = ((int)(feature[i] * discretization))/(float)discretization;
    }
}

const char* AreaFeatureExtractor::getFeatureName(){
    return "AreaFeature";
}

