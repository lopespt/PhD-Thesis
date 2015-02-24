
#include "AreaFeatureFactory.hpp"
#include "AreaFeature.hpp"

#include <opencv/cv.h>

AreaFeatureFactory::AreaFeatureFactory(int discretization):FeatureFactoryAbstract(1), discretization(discretization){
}

FeatureAbstractPtr AreaFeatureFactory::CreateFromRegion(const Region* region) const{
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
    return FeatureAbstractPtr(new AreaFeature(vect));
}


FeatureAbstractPtr AreaFeatureFactory::CreateFromStream(istream &stream) const{
    AreaFeature* temp = new AreaFeature(0);
    int type;
    stream >> type;
    stream.ignore();
    stream >> temp->content;
    FeatureAbstractPtr f= FeatureAbstractPtr(move(temp));
    return f;
}

