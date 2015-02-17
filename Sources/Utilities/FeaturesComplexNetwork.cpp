#include "FeaturesComplexNetwork.hpp"
#include <string.h>
#include <QDataStream>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include <lemon/lgf_reader.h>
#include <lemon/graph_to_eps.h>
#include <lemon/planarity.h>
#include <FeatureExtractors/FeatureAbstract.hpp>

using namespace std;



FeaturesComplexNetwork::FeaturesComplexNetwork():ComplexNetwork()
{
}

void FeaturesComplexNetwork::save(const char* filename){
    digraphWriter(*this, filename).arcMap("arcs", this->arcs)
            .nodeMap("nodes", this->nodes)
            .run();
}

void FeaturesComplexNetwork::load(const char *filename, QList< FeatureFactoryAbstract* >& l){
    clear();
    NodeReader r(l);
    digraphReader(*this, filename)
            .nodeMap("nodes", this->nodes, r)
            .arcMap("arcs", this->arcs)
            .run();

    //Atualiza o indice Hash
    refreshCache();
}

void FeaturesComplexNetwork::refreshCache(){
    featureIndex.clear();
    for(ListDigraph::NodeIt it(*this); it != INVALID; ++it){
        featureIndex.insert(FeatureAbstractKey(nodes[it]), it);
    }
}


FeaturesComplexNetwork::~FeaturesComplexNetwork(){
    //clear();
}

float FeaturesComplexNetwork::getOutputDegree(Node from) const{
    float total=0;
    for(OutArcIt e(*this, from); e != INVALID; ++e){
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


FeaturesComplexNetwork::Node FeaturesComplexNetwork::getNodeFromFeature(const FeatureAbstract *f) const{
    if(featureIndex.contains(FeatureAbstractKey(f))){
        return featureIndex[FeatureAbstractKey(f)];
    }
    return Node(INVALID);
}

FeatureAbstractPtr FeaturesComplexNetwork::NodeReader::operator()(const string& str){
    std::stringstream stream;
    stream << str;
    int type;
    sscanf(str.c_str(), "%d", &type);
    for(FeatureFactoryAbstract* f : factories){
        if(f->getType() == type){
            FeatureAbstractPtr feat= f->CreateFromStream(stream);
            return feat;
        }
    }
    throw new runtime_error("No FeatureFactory Found");
    return FeatureAbstractPtr();
}
