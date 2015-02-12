#include "FeatureAbstract.hpp"
#include <string.h>
#include <QHash>
#include <QByteArray>
#include <QString>
#include <iostream>
#include <vector>
#include "AreaFeatureFactory.hpp"
#include "LabelFeatureFactory.hpp"
#include "OrientationFeatureFactory.hpp"

FeatureAbstract::FeatureAbstract(int type, const char *featureName):type(type), featureName(featureName){

}

bool FeatureAbstract::operator <(const FeatureAbstract& other) const{
    if(this->getType() != other.getType())
        return other.getType() - this->getType();
    return memcmp(this->data, other.data, data_size);
}


bool FeatureAbstract::operator==(const FeatureAbstract& other) const{
    if(this->getType() != other.getType())
        return false;
    return memcmp(this->data, other.data, this->data_size)==0;

}

uint qHash(const FeatureAbstractKey& v){
    return qHash(QString(v.pointer->getType()).append(QByteArray( (const char*)v.pointer->data, v.pointer->data_size )));
}

std::ostream & operator<<(ostream& os, const FeatureAbstractPtr& node){
    node.get()->WriteToStream(os);
    return os;
}

