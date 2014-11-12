#include "FeatureAbstract.hpp"
#include <string.h>
#include <QHash>
#include <QByteArray>
#include <QString>

FeatureAbstract::FeatureAbstract(int type, const char *featureName):type(type), featureName(featureName){

}

bool FeatureAbstract::operator <(const FeatureAbstract& other) const{
    int cmp = strcmp(this->featureName, other.getFeatureName());
    if(cmp!=0)
        return cmp;
    return memcmp(this->data, other.data, data_size);
}


bool FeatureAbstract::operator==(const FeatureAbstract& other) const{
    char b1[40];
    char b2[40];
    if(strcmp(this->asString(b1), other.asString(b2))!=0)
        return false;

    return memcmp(this->data, other.data, this->data_size)==0;

}


uint qHash(const FeatureAbstractKey& v){
    char buffer[40];
    return qHash(QString(v.pointer->asString(buffer)).append(QByteArray( (const char*)v.pointer->data, v.pointer->data_size )));
}
