//
// Created by Guilherme Wachs on 18/06/15.
//

#ifndef PHDTHESIS_SHAPESIGNATUREFEATUREFACTORY_H
#define PHDTHESIS_SHAPESIGNATUREFEATUREFACTORY_H


#include "FeatureFactoryAbstract.hpp"
#include "FeatureAbstract.hpp"

class ShapeSignatureFeatureFactory: public FeatureFactoryAbstract {

private:
    int angleDiscretization;
    int distanceDiscretization;
public:

    ShapeSignatureFeatureFactory(int angleDiscretization, int distanceDiscretization);

    virtual FeatureAbstractPtr CreateFromRegion(const Region *r) const override;

    virtual FeatureAbstractPtr CreateFromStream(istream &stream) const override;
};


#endif //PHDTHESIS_SHAPESIGNATUREFEATUREFACTORY_H
