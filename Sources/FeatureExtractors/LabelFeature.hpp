#ifndef LABELFEATURE_HPP
#define LABELFEATURE_HPP

#include "Feature.hpp"

class QDataStream;
class LabelFeatureFactory;

typedef struct _label label;
struct _label{
    char value[50];
    _label(){value[0]='\0';}
    _label(const char *val){
        strcpy(value, val);
    }
};

class LabelFeature:public Feature<label>
{
public:
    LabelFeature(label value);
    const char* asString(char *buffer) const;
    void WriteToStream(std::ostream &stream) const;

    friend class LabelFeatureFactory;

    virtual ~LabelFeature(){
    }
};

#endif // LABELFEATURE_HPP
