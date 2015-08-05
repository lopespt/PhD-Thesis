//
// Created by Guilherme Wachs on 18/06/15.
//

#include "ShapeSignatureFeatureFactory.h"
#include "Region.hpp"

ShapeSignatureFeatureFactory::ShapeSignatureFeatureFactory(int angleDiscretization, int distanceDiscretization)
        : FeatureFactoryAbstract(4),
          angleDiscretization(angleDiscretization),
        distanceDiscretization(distanceDiscretization)
{

}

FeatureAbstractPtr ShapeSignatureFeatureFactory::CreateFromRegion(const Region *r) const {
    QPoint center = r->getMask().getCenter();
    QVector<int> dist(angleDiscretization);

    for(float angle=0; angle<360; angle+=360.0/angleDiscretization) {
        QLineF l = QLineF::fromPolar(10, angle);
    }



    return FeatureAbstractPtr();
}

FeatureAbstractPtr ShapeSignatureFeatureFactory::CreateFromStream(istream &stream) const {
    return FeatureAbstractPtr();
}
