#include "LabelFeatureFactory.hpp"
#include "LabelFeature.hpp"
LabelFeatureFactory::LabelFeatureFactory():FeatureFactoryAbstract(0)
{
}


shared_ptr<FeatureAbstract> LabelFeatureFactory::CreateFromRegion(const Region* region) const{
    label l;
    strcpy(l.value,region->getLabel().toStdString().c_str());
    auto feature = make_shared<LabelFeature>(l);
    return feature;
}

shared_ptr<FeatureAbstract> LabelFeatureFactory::CreateFromStream(QDataStream &stream) const{
    label l;
    stream.readRawData((char*)&l, sizeof(label));
    auto feature = make_shared<LabelFeature>(l);
    return feature;
}
