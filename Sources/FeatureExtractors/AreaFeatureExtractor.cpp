
#include "AreaFeatureExtractor.hpp"
#include "AreaFeature.hpp"

AreaFeatureExtractor::AreaFeatureExtractor(int discretization):FeatureExtractorAbstract(), discretization(discretization){
}

FeatureAbstract* AreaFeatureExtractor::doExtraction(const Region* region){
    float vect;
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
    vect = area / (region->getBoundaryRect().width() * region->getBoundaryRect().height());
    //Discretization

    vect = ((int)(vect * discretization))/(float)discretization;
    return new AreaFeature(vect);
}

