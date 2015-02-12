#include "LabelFeature.hpp"
#include <string.h>

LabelFeature::LabelFeature(label l):Feature<label>(l,0,"LabelFeature")
{
    memset((void*)&content,0,sizeof(label));
    strcpy(this->content.value, l.value);
}


const char* LabelFeature::asString(char *buffer) const{
    strcpy(buffer, this->content.value);
    return buffer;
}

void LabelFeature::WriteToStream(std::ostream &stream) const{
    stream << type << "," << content.value;
}
