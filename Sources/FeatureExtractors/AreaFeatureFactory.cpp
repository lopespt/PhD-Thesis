
#include "AreaFeatureFactory.hpp"
#include "AreaFeature.hpp"

#include <opencv/cv.h>

AreaFeatureFactory::AreaFeatureFactory(int discretization):FeatureFactoryAbstract(1), discretization(discretization){
}

FeatureAbstractPtr AreaFeatureFactory::CreateFromRegion(const Region* region) const{
    float vect;
    region->getMask();
    float area = 0;
    //bool ok;
    /*for(int i=0;i<region->getBoundaryRect().width();i++){
        for(int j=0;j<region->getBoundaryRect().height();j++){
           ok = region->getBoundary().containsPoint(QPoint(i,j), Qt::OddEvenFill);
           if(ok)
               area++;
        }
    }*/
    QPolygon boundary = region->getBoundary();
    for(unsigned int i=0; i< boundary.size() - 1;i++){
        area += ( 1.0*boundary[i].x()*boundary[i+1].y() - 1.0*boundary[i+1].x()*boundary[i].y() );
    }
    area += ( 1.0*boundary.last().x()*boundary[0].y() - 1.0*boundary[0].x()*boundary.last().y() );
    area = fabs(area)/2.0;

    vect = area / (region->getImage()->width() * region->getImage()->height());

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

