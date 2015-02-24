#include "AreaFeature.hpp"

#include <stdlib.h>
#include <memory>
#include <ostream>
#include <QHash>

AreaFeature::AreaFeature(float content):Feature<float>(content, 1, "AreaFeature")
{
}

const char *AreaFeature::asString(char *buffer) const {
    sprintf(buffer, "area(%f)", this->content);
    return buffer;
}

uint AreaFeature::getHash() const{
    return qHash(getType()) ^ qHash(content);
}

void AreaFeature::WriteToStream(std::ostream &stream) const{
    stream << type << "," << content;
}
