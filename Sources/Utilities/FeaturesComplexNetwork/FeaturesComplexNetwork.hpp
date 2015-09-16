#ifndef FEATURESCOMPLEXNETWORK_HPP
#define FEATURESCOMPLEXNETWORK_HPP

#include <lemon/list_graph.h>
#include "Link.hpp"
#include <QHash>
#include<QList>
#include <memory>
#include <exception>
#include "SameObjectLink.hpp"
#include "DynLinkLookUp.hpp"
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include <lemon/lgf_reader.h>

using namespace lemon;
class FeatureFactoryAbstract;
class FeatureAbstractPtr;

class FeaturesComplexNetwork : public ListDigraph {
public:
    template<typename T>
    using NMap = ListDigraph::NodeMap<T>;


    template<typename T>
    using AMap = ListDigraph::ArcMap<T>;

private:

    NMap<FeatureAbstractPtr> nodes;
    AMap<Link> arcs;

    QHash<FeatureAbstractPtr, Node> featureIndex;
    QHash<ListDigraph::Arc, Link> sameLabelLinks;
    QHash<ListDigraph::Arc, Link> otherLabelLinks;

    void load(const char *filename) {
    }

    ListDigraph::Node addNode() {
        return ListDigraph::addNode();
    };

    Arc addArc(const Node &from, const Node &to) {
        return ListDigraph::addArc(from,to);
    };


public:
    friend class DigraphReader<FeaturesComplexNetwork>;

    void save(const char *filename);

    void load(const char *filename, const QList<const FeatureFactoryAbstract *> &l);


    float getOutputWeightedDegree(Node) const;

    float getInputWeightedDegree(Node) const;


    Node getNodeFromFeature(const FeatureAbstractPtr &f) const;

    /*
    FeatureAbstractPtr getNodeFeature(const Node &a) const;
    Link getLinkFromNodes(const Node &a, const Node &b) const;
    Link getLinkFromNodes(const FeatureAbstractPtr &a, const FeatureAbstractPtr &b) const;
    SameObjectLink getSameObjectLinkFromNodes(const Node &a, const Node &b) const;
    SameObjectLink getSameObjectLinkFromNodes(const FeatureAbstractPtr &a, const FeatureAbstractPtr &b) const;
*/
    void refreshCache();

    ListDigraph::Node addNode(const FeatureAbstractPtr &value);

    ListDigraph::Arc addArc(const ListDigraph::Node &from, const ListDigraph::Node &to, const Link &link);

    void erase(Node n);

    void erase(Arc a);

    FeaturesComplexNetwork();


    ~FeaturesComplexNetwork();
};

namespace lemon {
    uint qHash(const lemon::ListDigraph::Arc &a);
}
#endif // FEATURESCOMPLEXNETWORK_HPP

