#ifndef AREAFEATURE_HPP
#define AREAFEATURE_HPP

#include "Feature.hpp"

class QDataStream;
class AreaFeatureFactory;

class AreaFeature:public Feature<float>
{
public:
    AreaFeature(float value);
    const char* asString(char *buffer) const;
    void WriteToStream(QDataStream &stream) const;

    friend class AreaFeatureFactory;

};

#endif // AREAFEATURE_HPP
