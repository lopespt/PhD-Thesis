#include "LabelFeatureFactory.hpp"
#include "LabelFeature.hpp"
#include "Region.hpp"
#include <istream>

LabelFeatureFactory::LabelFeatureFactory():FeatureFactoryAbstract(0)
{
}


FeatureAbstractPtr LabelFeatureFactory::CreateFromRegion(const Region* region) const{
    label l;
    QString labelStr = region->getLabel();
    strcpy(l.value, labelStr.toStdString().c_str());
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
