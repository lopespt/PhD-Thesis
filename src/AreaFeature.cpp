
#include "AreaFeature.hpp"

AreaFeature::AreaFeature(Region* region):Feature(region){
    this->vector.resize(1);
}

void AreaFeature::extractFeature(){
    float area = 0;
    bool ok;
    for(int i=0;i<region->getBoundaryRect().width();i++){
        for(int j=0;j<region->getBoundaryRect().height();j++){
           region->getPixelRelative(i,j, &ok); 
           if(ok)
               area++;
        }
    }
    this->vector[0] = area / (this->region->getBoundaryRect().width() * this->region->getBoundaryRect().height());
}
