#include "FeatureFactoryAbstract.hpp"

FeatureFactoryAbstract::FeatureFactoryAbstract(int type):type(type)
{
}

int FeatureFactoryAbstract::getType() const{
    return type;
}
