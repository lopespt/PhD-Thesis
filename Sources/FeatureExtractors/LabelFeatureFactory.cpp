#include "LabelFeatureFactory.hpp"

#include "LabelFeature.hpp"

LabelFeatureFactory::LabelFeatureFactory():FeatureFactoryAbstract(0)
{
}


FeatureAbstract* LabelFeatureFactory::CreateFromRegion(const Region* region) const{
    label l;
    strcpy(l.value,region->getLabel().toStdString().c_str());
    LabelFeature* feature = new LabelFeature(l);
    return feature;
}

FeatureAbstract* LabelFeatureFactory::CreateFromStream(QDataStream &stream) const{
    label l;
    stream.readRawData((char*)&l, sizeof(label));
    LabelFeature* feature = new LabelFeature(l);
    return feature;
}
