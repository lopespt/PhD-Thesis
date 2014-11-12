#ifndef FEATURESCOMPLEXNETWORK_HPP
#define FEATURESCOMPLEXNETWORK_HPP
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include "Link.hpp"

class FeatureFactoryAbstract;

class FeaturesComplexNetwork:public ComplexNetwork<const FeatureAbstract*, Link>
{
private:
    virtual void load(const char *filename){}
public:
    FeaturesComplexNetwork();
    void save(const char* filename);
    void load(const char* filename, QList<FeatureFactoryAbstract*>);
};

#endif // FEATURESCOMPLEXNETWORK_HPP
