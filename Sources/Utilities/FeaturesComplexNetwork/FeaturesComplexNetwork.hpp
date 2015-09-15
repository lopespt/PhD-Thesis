#ifndef FEATURESCOMPLEXNETWORK_HPP
#define FEATURESCOMPLEXNETWORK_HPP

#include <lemon/list_graph.h>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include "Link.hpp"
#include <QHash>
#include<QList>
#include <memory>
#include <exception>

using namespace lemon;
class FeatureFactoryAbstract;

class FeaturesComplexNetwork : private ListDigraph {
private:
    typedef typename ListDigraph::NodeMap<FeatureAbstractPtr> NMap;
    typedef typename ListDigraph::ArcMap<Link> AMap;

    mutable std::mutex mtxN;
    mutable std::mutex mtxE;

    NMap nodes;
    AMap arcs;

    QHash<FeatureAbstractPtr, Node> featureIndex;

    void load(const char *filename) { }


public:
    FeaturesComplexNetwork();
    ~FeaturesComplexNetwork();

    void save(const char *filename);
    void load(const char *filename, const QList<const FeatureFactoryAbstract *> &l);


    float getOutputWeightedDegree(Node) const;
    float getInputWeightedDegree(Node) const;


    Node getNodeFromFeature(const FeatureAbstractPtr &f) const;

    void refreshCache();

};

#endif // FEATURESCOMPLEXNETWORK_HPP

