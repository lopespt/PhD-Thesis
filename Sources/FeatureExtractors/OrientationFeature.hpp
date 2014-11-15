#ifndef ORIENTATIONFEATURE_HPP
#define ORIENTATIONFEATURE_HPP

#include "Feature.hpp"

class OrientationFeature:public Feature<unsigned int>
{
public:
    OrientationFeature(unsigned int value);
    const char * asString(char *buffer) const;
    void WriteToStream(QDataStream &stream) const;
};

#endif // ORIENTATIONFEATURE_HPP
