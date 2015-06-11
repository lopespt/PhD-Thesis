#include "AreaFeature.hpp"

#include <ostream>
#include <QHash>

AreaFeature::AreaFeature(unsigned int content) : Feature<unsigned int>(content, 1, "AreaFeature") {
}

const char *AreaFeature::asString(char *buffer) const {
    sprintf(buffer, "area(%u)", this->content);
    return buffer;
}

uint AreaFeature::getHash() const {
    return qHash(getType()) ^ qHash(content);
}

void AreaFeature::WriteToStream(std::ostream &stream) const {
    stream << type << "," << content;
}
