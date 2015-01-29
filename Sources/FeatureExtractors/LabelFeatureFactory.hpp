#ifndef LABELFEATUREFACTORY_HPP
#define LABELFEATUREFACTORY_HPP

#include "FeatureFactoryAbstract.hpp"
#include <memory>
using namespace std;
class LabelFeatureFactory:public FeatureFactoryAbstract
{
public:
    LabelFeatureFactory();
    shared_ptr<FeatureAbstract> CreateFromRegion(const Region* region) const;
    shared_ptr<FeatureAbstract> CreateFromStream(QDataStream &stream) const;

};

#endif // LABELFEATUREFACTORY_HPP
