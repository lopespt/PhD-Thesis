#ifndef FEATURESCOMPLEXNETWORK_HPP
#define FEATURESCOMPLEXNETWORK_HPP
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include "Link.hpp"
#include <QHash>
#include<QList>
#include <memory>
class FeatureFactoryAbstract;

class FeaturesComplexNetwork:public ComplexNetwork< std::shared_ptr<const FeatureAbstract> , Link>
{
private:
    QHash<FeatureAbstractKey, node_id> featureIndex;
    virtual void load(const char *filename){}

    typedef struct{
        char description[200];
        unsigned int num_nodes;
        unsigned int num_edges;
    }header;

public:
    FeaturesComplexNetwork();
    ~FeaturesComplexNetwork();
    void save(const char* filename);
    void load(const char* filename, QList<FeatureFactoryAbstract*>);
    float getOutputDegree(node_id) const;
    void clear();
    //bool removeNode(node_id id);
    void updateIndex();
    node_id getNodeFromFeature(const FeatureAbstract* f) const;
    QList<node_id> getNodesOfSameLabel(node_id);
};
#endif // FEATURESCOMPLEXNETWORK_HPP
