#include "OrientationFeature.hpp"

OrientationFeature::OrientationFeature(unsigned int value):Feature<unsigned int>(value, 2, "Orientation")
{
}

const char* OrientationFeature::asString(char *buffer) const{
    sprintf(buffer,"ori(%u)", this->content);
    return buffer;
}

void OrientationFeature::WriteToStream(std::ostream &stream) const{
    stream << type << "," << this->content;
}
