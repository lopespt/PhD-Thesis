#ifndef LABELFEATUREFACTORY_HPP
#define LABELFEATUREFACTORY_HPP

#include "FeatureFactoryAbstract.hpp"
#include <memory>
#include <QtGlobal>
class Region;

using namespace std;
class LabelFeatureFactory:public FeatureFactoryAbstract
{
public:
    LabelFeatureFactory();
    FeatureAbstractPtr CreateFromRegion(const Region* region) const;
    FeatureAbstractPtr CreateFromStream(istream &stream) const;
};

#endif // LABELFEATUREFACTORY_HPP
