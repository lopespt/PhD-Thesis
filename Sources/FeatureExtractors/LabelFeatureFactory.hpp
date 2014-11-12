#ifndef LABELFEATUREFACTORY_HPP
#define LABELFEATUREFACTORY_HPP

#include "FeatureFactoryAbstract.hpp"

class LabelFeatureFactory:public FeatureFactoryAbstract
{
public:
    LabelFeatureFactory();
    FeatureAbstract* CreateFromRegion(const Region* region) const;
    FeatureAbstract* CreateFromStream(QDataStream &stream) const;

};

#endif // LABELFEATUREFACTORY_HPP
