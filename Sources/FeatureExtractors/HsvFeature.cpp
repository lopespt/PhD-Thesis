#include "HsvFeature.hpp"
#include <iostream>
#include <QHash>
#include <QByteArray>


HsvFeature::HsvFeature(vector<int> content):Feature<vector<int>>(content, 3, "Hsv")
{
}

const char* HsvFeature::asString(char *buffer) const{
    char *start=buffer;
    for(int i=0; i < content.size(); i++){
        buffer += sprintf(buffer, "%-2d ", content[i]);
    }
    return start;
}

uint HsvFeature::getHash() const{
    QByteArray a((char*)content.data(), sizeof(int) * content.size());
    a.prepend("hsv");
    return qHash(a);
}

void HsvFeature::WriteToStream(ostream &stream) const{
    stream << type << " ";
    for(int i=0; i < content.size(); i++){
        stream << content[i];
        stream << " ";
    }
}

bool HsvFeature::operator <(const FeatureAbstract& other) const{
    if(this->getType() != other.getType())
        return other.getType() - this->getType();

    return this->content < dynamic_cast<const HsvFeature*>(&other)->content;
}

bool HsvFeature::operator ==(const FeatureAbstract& other) const{
    if(this->getType() != other.getType())
        return false;

    return this->content == dynamic_cast<const HsvFeature*>(&other)->content;
}

HsvFeature::~HsvFeature()
{
}

