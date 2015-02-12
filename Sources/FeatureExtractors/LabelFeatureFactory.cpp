#include "LabelFeatureFactory.hpp"
#include "LabelFeature.hpp"
LabelFeatureFactory::LabelFeatureFactory():FeatureFactoryAbstract(0)
{
}


FeatureAbstractPtr LabelFeatureFactory::CreateFromRegion(const Region* region) const{
    label l;
    strcpy(l.value,region->getLabel().toStdString().c_str());
    FeatureAbstractPtr feature = FeatureAbstractPtr( new LabelFeature(l));
    fflush(stdout);
    return feature;
}

FeatureAbstractPtr LabelFeatureFactory::CreateFromStream(istream &stream) const{
    label l;
    int type;
    char buffer[50];
    char *pt;
    stream.getline(buffer, 50);
    pt = strtok(buffer,",");
    sscanf(pt,"%d", &type);
    pt = strtok(NULL,",");
    strcpy(l.value, pt);
    return FeatureAbstractPtr(new LabelFeature(l));
}
