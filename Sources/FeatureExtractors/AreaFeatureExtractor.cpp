
#include "AreaFeatureExtractor.hpp"

AreaFeatureExtractor::AreaFeatureExtractor(){
}

QVector<float> AreaFeatureExtractor::doExtraction(const Region *region, int discretization){
    QVector<float> vect(1);
    region->getMask();
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
    //Discretization

    for(int i=0;i<vect.size();i++)
        vect[i] = ((int)(vect[i] * discretization))/(float)discretization;
    return vect;
}

const char* AreaFeatureExtractor::getFeatureName(){
    return "AreaFeature";
}

