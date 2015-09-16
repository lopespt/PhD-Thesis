#include "FeaturesComplexNetwork.hpp"
#include <QDataStream>
#include <lemon/lgf_reader.h>
#include <lemon/graph_to_eps.h>

using namespace std;

uint lemon::qHash(const ListDigraph::Arc &a){
    uint ret = (uint) ListDigraph::id(a);
    printf("%d\n", ret);
    return ret;
}

class NodeReader {
private:
    const QList<const FeatureFactoryAbstract *> &factories;
public:
    NodeReader(const QList<const FeatureFactoryAbstract *> &factories) : factories(factories) { }

    FeatureAbstractPtr operator()(const string &str);
};

FeaturesComplexNetwork::FeaturesComplexNetwork() : ListDigraph(), arcs(*this), nodes(*this) {
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
    for (ListDigraph::NodeIt it(*this); it != INVALID; ++it) {
        featureIndex.insert(nodes[it], it);
    }


    for (ListDigraph::ArcIt it(*this); it != INVALID; ++it) {
        switch (arcs[it].type){
            case Link::LinkType::OtherLabel:
                otherLabelLinks[it] = arcs[it];
                break;
            case Link::LinkType::SameLabel:
                sameLabelLinks[it] = arcs[it];
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
    auto newNode = ListDigraphBase::Node();
    featureIndex[value] = newNode;
    nodes[newNode] = value;
    return newNode;

}

ListDigraph::Arc FeaturesComplexNetwork::addArc(const ListDigraph::Node &from, const ListDigraph::Node &to,
                                                    const Link &link) {


    return ListDigraphBase::Arc();
}

void FeaturesComplexNetwork::erase(ListDigraphBase::Node n) {
    for( OutArcIt it(*this, n); it != INVALID; ++it ){
        sameLabelLinks.remove(it);
        otherLabelLinks.remove(it);
    }
    ListDigraph::erase(n);
}

void FeaturesComplexNetwork::erase(ListDigraphBase::Arc a) {
    sameLabelLinks.remove(a);
    otherLabelLinks.remove(a);
    ListDigraph::erase(a);
}
