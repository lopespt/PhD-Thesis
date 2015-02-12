#include "AreaFeature.hpp"

#include <stdlib.h>

AreaFeature::AreaFeature(float content):Feature<float>(content, 1, "AreaFeature")
{
}

const char *AreaFeature::asString(char *buffer) const {
    sprintf(buffer, "area(%f)", this->content);
    return buffer;
}

void AreaFeature::WriteToStream(std::ostream &stream) const{
    stream << type << "," << content;
}
