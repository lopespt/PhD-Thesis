
#include "AreaFeatureFactory.hpp"
#include "AreaFeature.hpp"

AreaFeatureFactory::AreaFeatureFactory(int discretization):FeatureFactoryAbstract(1), discretization(discretization){
}

shared_ptr<FeatureAbstract> AreaFeatureFactory::CreateFromRegion(const Region* region) const{
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
    return shared_ptr<FeatureAbstract>(new AreaFeature(vect));
}

shared_ptr<FeatureAbstract> AreaFeatureFactory::CreateFromStream(QDataStream &stream) const{
    shared_ptr<FeatureAbstract> f= shared_ptr<FeatureAbstract>(new AreaFeature(0));
    stream >> ((AreaFeature*)f.get())->content;
    return f;
}

