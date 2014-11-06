#include "AreaFeature.hpp"

#include <stdlib.h>

AreaFeature::AreaFeature(float content):Feature<float>(content, "AreaFeature")
{
}

const char *AreaFeature::asString(char *buffer) const {
    sprintf(buffer, "%f", this->content);
    return buffer;
}
