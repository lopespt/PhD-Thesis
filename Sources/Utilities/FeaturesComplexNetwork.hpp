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
    ~FeaturesComplexNetwork();
    void save(const char* filename);
    void load(const char* filename, QList<FeatureFactoryAbstract*>);
    float getOutputDegree(node_id) const;
    void clear();
    bool removeNode(node_id id);

};

#endif // FEATURESCOMPLEXNETWORK_HPP
