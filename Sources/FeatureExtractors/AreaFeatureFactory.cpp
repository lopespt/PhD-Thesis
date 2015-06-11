#include "AreaFeatureFactory.hpp"
#include "AreaFeature.hpp"

AreaFeatureFactory::AreaFeatureFactory(int discretization) : FeatureFactoryAbstract(1), discretization(discretization) {
}

FeatureAbstractPtr AreaFeatureFactory::CreateFromRegion(const Region *region) const {
    unsigned int vect;
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
    QPolygon boundary = region->getMask().getBoundary();
    for (unsigned int i = 0; i < boundary.size() - 1; i++) {
        area += (1.0 * boundary[i].x() * boundary[i + 1].y() - 1.0 * boundary[i + 1].x() * boundary[i].y());
    }
    area += (1.0 * boundary.last().x() * boundary[0].y() - 1.0 * boundary[0].x() * boundary.last().y());
    area = fabs(area) / 2.0f;

    float perc_area = (area / (region->getImage()->width() * region->getImage()->height()));

    //Discretization

    vect = (unsigned int) (perc_area * discretization + 0.5);
    return FeatureAbstractPtr(new AreaFeature(vect));
}


FeatureAbstractPtr AreaFeatureFactory::CreateFromStream(istream &stream) const {
    int type;
    float value;
    stream >> type;
    stream.ignore();
    stream >>  value;
    FeatureAbstractPtr f = FeatureAbstractPtr(new AreaFeature(value));
    return f;
}

