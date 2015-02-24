#include "LabelFeature.hpp"
#include <string.h>
#include <memory>
#include <ostream>
#include <QHash>
#include <QByteArray>

LabelFeature::LabelFeature(label l):Feature<label>(l,0,"LabelFeature")
{
    memset((void*)&content,0,sizeof(label));
    strcpy(this->content.value, l.value);
}

uint LabelFeature::getHash() const{
    QByteArray a(content.value);
    a.prepend("label");
    return qHash(a);
}

const char* LabelFeature::asString(char *buffer) const{
    strcpy(buffer, this->content.value);
    return buffer;
}

void LabelFeature::WriteToStream(std::ostream &stream) const{
    stream << type << "," << content.value;
}
