#include "OrientationFeature.hpp"

OrientationFeature::OrientationFeature(unsigned int value):Feature<unsigned int>(value, 2, "Orientation")
{
}

const char* OrientationFeature::asString(char *buffer) const{
    sprintf(buffer,"|%u|", this->content);
    return buffer;
}

void OrientationFeature::WriteToStream(QDataStream &stream) const{
    stream.writeRawData((char*)&this->content, sizeof(unsigned int));
}
