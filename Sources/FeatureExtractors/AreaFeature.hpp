#ifndef AREAFEATURE_HPP
#define AREAFEATURE_HPP

#include "Feature.hpp"


class AreaFeature:public Feature<float>
{
public:
    AreaFeature(float value);
    const char* asString(char* buffer) const;

};

#endif // AREAFEATURE_HPP
