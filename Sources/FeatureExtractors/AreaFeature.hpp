#ifndef AREAFEATURE_HPP
#define AREAFEATURE_HPP

#include "Feature.hpp"

class QDataStream;

class AreaFeatureFactory;

class AreaFeature : public Feature<unsigned int> {
public:
    AreaFeature(unsigned int value);

    const char *asString(char *buffer) const;

    void WriteToStream(std::ostream &stream) const;

    uint getHash() const;

    friend class AreaFeatureFactory;

};

#endif // AREAFEATURE_HPP
