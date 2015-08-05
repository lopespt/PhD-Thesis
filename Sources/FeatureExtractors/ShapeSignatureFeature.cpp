//
// Created by Guilherme Wachs on 18/06/15.
//

#include <QtCore/qbytearray.h>
#include "ShapeSignatureFeature.h"
#include <QHash>
#include <iostream>

ShapeSignatureFeature::ShapeSignatureFeature(vector<int> content)
        : Feature(content, 4,"ShapeSignature") {
}

const char *ShapeSignatureFeature::asString(char *buffer) const {
        char *start = buffer;
        for (unsigned int i = 0; i < content.size(); i++) {
                start += sprintf(start, "%-2d ", content[i]);
        }
}

uint ShapeSignatureFeature::getHash() const {
        QByteArray a((char *) content.data(), sizeof(int) * content.size());
        a.prepend("sig");
        return qHash(a);
}

void ShapeSignatureFeature::WriteToStream(std::ostream &stream) const {
    stream << type << " ";
    for (unsigned int i = 0; i < content.size(); i++) {
        stream << content[i];
        stream << " ";
    }
}

bool ShapeSignatureFeature::operator==(const FeatureAbstract &other) const {
    if (this->getType() != other.getType())
        return false;

    return this->content == dynamic_cast<const ShapeSignatureFeature *>(&other)->content;
}

bool ShapeSignatureFeature::operator<(const FeatureAbstract &other) const {
    if (this->getType() != other.getType())
        return other.getType() - this->getType();

    return this->content < dynamic_cast<const ShapeSignatureFeature *>(&other)->content;
}
