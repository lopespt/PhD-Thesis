#ifndef LABELFEATURE_HPP
#define LABELFEATURE_HPP

#include "Feature.hpp"

class QDataStream;
class LabelFeatureFactory;

typedef struct{
    char value[50];
}label;

class LabelFeature:public Feature<label>
{
public:
    LabelFeature(label value);
    const char* asString(char *buffer) const;
    void WriteToStream(QDataStream &stream) const;

    friend class LabelFeatureFactory;
};

#endif // LABELFEATURE_HPP
