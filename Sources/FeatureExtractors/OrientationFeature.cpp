#include "OrientationFeature.hpp"
#include <memory>
#include <ostream>
#include <QHash>
#include <QByteArray>

OrientationFeature::OrientationFeature(unsigned int value):Feature<unsigned int>(value, 2, "Orientation")
{
}

uint OrientationFeature::getHash() const{
    QByteArray a("ori");
    a.append((char*)&content, sizeof(unsigned int));
    return qHash(a);
}

const char* OrientationFeature::asString(char *buffer) const{
    sprintf(buffer,"ori(%u)", this->content);
    return buffer;
}

void OrientationFeature::WriteToStream(std::ostream &stream) const{
    stream << type << "," << this->content;
}
