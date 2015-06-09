#ifndef FEATURESCOMPLEXNETWORK_HPP
#define FEATURESCOMPLEXNETWORK_HPP

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include "Link.hpp"
#include <QHash>
#include<QList>
#include <memory>
#include <exception>

class FeatureFactoryAbstract;

class FeaturesComplexNetwork : public ComplexNetwork<FeatureAbstractPtr, Link> {
private:
    QHash<FeatureAbstractPtr, Node> featureIndex;

    void load(const char *filename) { }

    typedef struct {
        char description[200];
        unsigned int num_nodes;
        unsigned int num_edges;
    } header;

public:
    FeaturesComplexNetwork();

    ~FeaturesComplexNetwork();

    void save(const char *filename);

    void load(const char *filename, const QList<const FeatureFactoryAbstract *> &l);

    float getOutputDegree(Node) const;

    //bool removeNode(node_id id);
    Node getNodeFromFeature(const FeatureAbstractPtr &f) const;

    void refreshCache();

    class NodeReader {
    private:
        const QList<const FeatureFactoryAbstract *> &factories;
    public:
        NodeReader(const QList<const FeatureFactoryAbstract *> &factories) : factories(factories) { }

        FeatureAbstractPtr operator()(const string &str);
    };
};

#endif // FEATURESCOMPLEXNETWORK_HPP

