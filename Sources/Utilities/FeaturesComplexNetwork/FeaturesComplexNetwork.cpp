#include "FeaturesComplexNetwork.hpp"
#include <QDataStream>
#include <lemon/lgf_reader.h>
#include <lemon/graph_to_eps.h>
#include <assert.h>

using namespace std;

uint lemon::qHash(const ListDigraph::Arc &a){
    uint ret = (uint) ListDigraph::id(a);
    return ret;
}

uint lemon::qHash(const ListDigraph::Node &a){
    uint ret = (uint) ListDigraph::id(a);
    return ret;
}

class NodeReader {
private:
    const QList<const FeatureFactoryAbstract *> &factories;
public:
    NodeReader(const QList<const FeatureFactoryAbstract *> &factories) : factories(factories) { }

    FeatureAbstractPtr operator()(const string &str);
};

FeaturesComplexNetwork::FeaturesComplexNetwork() : ListDigraph(), nodes(*this), arcs(*this) {
}

void FeaturesComplexNetwork::save(const char *filename) {
    digraphWriter(*this, filename).arcMap("arcs", this->arcs)
            .nodeMap("nodes", this->nodes)
            .run();
}

void FeaturesComplexNetwork::load(const char *filename, const QList<const FeatureFactoryAbstract *> &l) {
    clear();
    NodeReader r(l);
    digraphReader(*this, filename)
            .nodeMap("nodes", this->nodes, r)
            .arcMap("arcs", this->arcs)
            .run();

    //Atualiza o indice Hash
    refreshCache();
}

void FeaturesComplexNetwork::refreshCache() {
    featureIndex.clear();
    sameLabelLinks.clear();
    otherLabelLinks.clear();
    for (ListDigraph::NodeIt it(*this); it != INVALID; ++it) {
        featureIndex.insert(nodes[it], it);
    }

    for (ListDigraph::ArcIt it(*this); it != INVALID; ++it) {
        ArcKey arc(source(it), target(it));
        switch (arcs[it].type){
            case Link::LinkType::OtherLabel:
                otherLabelLinks[arc] = it;
                break;
            case Link::LinkType::SameLabel:
                sameLabelLinks[arc] = it;
                break;
        }
    }

}


FeaturesComplexNetwork::~FeaturesComplexNetwork() {
    //clear();
}

float FeaturesComplexNetwork::getOutputWeightedDegree(Node from) const {
    float total = 0;
    for (OutArcIt e(*this, from); e != INVALID; ++e) {
        total += this->arcs[e].getWeight();
    }
    return total;
}

float FeaturesComplexNetwork::getInputWeightedDegree(Node from) const {
    float total = 0;
    for (OutArcIt e(*this, from); e != INVALID; ++e) {
        total += this->arcs[e].getWeight();
    }
    return total;
}

/*
bool FeaturesComplexNetwork::removeNode(node_id id){
    assert(getNode(id));
    //delete (*getNode(id));
    return ComplexNetwork<shared_ptr<const FeatureAbstract*>, Link>::removeNode(id);
}*/


FeaturesComplexNetwork::Node FeaturesComplexNetwork::getNodeFromFeature(const FeatureAbstractPtr &f) const {
    FeaturesComplexNetwork::Node n;
    if (featureIndex.contains(f)) {
        n = featureIndex[f];
    }else {
        n = Node(INVALID);
    }
    return n;
}

FeatureAbstractPtr NodeReader::operator()(const string &str) {
    std::stringstream stream;
    stream << str;
    int type;
    sscanf(str.c_str(), "%d", &type);
    for (const FeatureFactoryAbstract *f : factories) {
        if (f->getType() == type) {
            FeatureAbstractPtr feat = f->CreateFromStream(stream);
            return feat;
        }
    }
    throw new runtime_error("No FeatureFactory Found");
    return FeatureAbstractPtr();
}

ListDigraph::Node FeaturesComplexNetwork::addNode(const FeatureAbstractPtr &value) {
    auto newNode = ListDigraph::addNode();
    featureIndex[value] = newNode;
    nodes[newNode] = value;
    return newNode;
}

ListDigraph::Arc FeaturesComplexNetwork::addArc(const ListDigraph::Node &from, const ListDigraph::Node &to,
                                                    const Link &link) {


    auto arc = ListDigraph::addArc(from, to);
    arcs[arc] = link;
    auto key = ArcKey(from, to);
    switch (link.type){
        case Link::LinkType::OtherLabel:
            otherLabelLinks[key] = arc;
            break;
        case Link::LinkType::SameLabel:
            sameLabelLinks[key] = arc;
            break;
    }
    return arc;
}

void FeaturesComplexNetwork::erase(ListDigraph::Node n) {
    for( OutArcIt it(*this, n); it != INVALID; ++it ){
        ArcKey arc(source(it), target(it));
        sameLabelLinks.remove(arc);
        otherLabelLinks.remove(arc);
    }
    for( InArcIt it(*this, n); it != INVALID; ++it ){
        ArcKey arc(source(it), target(it));
        sameLabelLinks.remove(arc);
        otherLabelLinks.remove(arc);
    }
    featureIndex.remove(nodes[n]);
    ListDigraph::erase(n);
}

void FeaturesComplexNetwork::erase(ListDigraph::Arc a) {
    ArcKey arc(source(a), target(a));
    sameLabelLinks.remove(arc);
    otherLabelLinks.remove(arc);
    ListDigraph::erase(a);
}

ListDigraph::Arc FeaturesComplexNetwork::getArc(const ListDigraph::Node &from,
                                                           const ListDigraph::Node &to, Link::LinkType type) const {
    if(type == Link::LinkType::OtherLabel) {
        auto it = otherLabelLinks.find(ArcKey(from, to));
        if (it != otherLabelLinks.end())
            return *it;
    }else if(type == Link::LinkType::SameLabel){
        auto it = sameLabelLinks.find(ArcKey(from, to));
        if (it != sameLabelLinks.end())
            return *it;
    }
    return INVALID;
}

Link& FeaturesComplexNetwork::getLinkArcValue(const ListDigraph::Node &from,
                                                               const ListDigraph::Node &to, Link::LinkType type) {
    if(type == Link::LinkType::OtherLabel) {
        auto it = otherLabelLinks.find(ArcKey(from, to));
        assert(  it != otherLabelLinks.end() );
        return arcs[*it];
    }else if(type == Link::LinkType::SameLabel){
        auto it = sameLabelLinks.find(ArcKey(from, to));
        assert(  it != sameLabelLinks.end() );
        return arcs[*it];
    }
    assert(1==2);
}

Link FeaturesComplexNetwork::getLinkArcValue(const ListDigraph::Node &from,
                                              const ListDigraph::Node &to, Link::LinkType type) const {
    if(type == Link::LinkType::OtherLabel) {
        auto it = otherLabelLinks.find(ArcKey(from, to));
        assert(  it != otherLabelLinks.end() );
        return arcs[*it];
    }else if(type == Link::LinkType::SameLabel){
        auto it = sameLabelLinks.find(ArcKey(from, to));
        assert(  it != sameLabelLinks.end() );
        puts("aqui");
        return arcs[*it];
    }
    assert(1==2);
}
bool FeaturesComplexNetwork::arcExists(const ListDigraph::Node &from, const ListDigraph::Node &to,
                                       Link::LinkType type) const{
    if(type == Link::LinkType::OtherLabel) {
        auto it = otherLabelLinks.find(ArcKey(from, to));
        return   it != otherLabelLinks.end();
    }else if(type == Link::LinkType::SameLabel){
        auto it = sameLabelLinks.find(ArcKey(from, to));
        return  it != sameLabelLinks.end() ;
    }
    return false;
}

Link FeaturesComplexNetwork::getLinkArcValue(const ListDigraph::Arc &a) const {
    return arcs[a];
}

int FeaturesComplexNetwork::getNumArcs() const{
    return sameLabelLinks.size()+otherLabelLinks.size();
}

int FeaturesComplexNetwork::getNumNodes() const {
    return featureIndex.size();
}

FeatureAbstractPtr& FeaturesComplexNetwork::getNode(const ListDigraph::Node &node) {
    return nodes[node];
}

FeatureAbstractPtr FeaturesComplexNetwork::getNode(const ListDigraph::Node &node) const {
    return nodes[node];
}

