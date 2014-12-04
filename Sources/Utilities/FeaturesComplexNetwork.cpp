#include "FeaturesComplexNetwork.hpp"
#include <string.h>
#include <QDataStream>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>

using namespace std;

FeaturesComplexNetwork::FeaturesComplexNetwork():ComplexNetwork()
{
}

void FeaturesComplexNetwork::save(const char* filename){
    QFile f(filename);
    f.open(QIODevice::WriteOnly);
    QDataStream stream(&f);



    header f_header;
    strcpy(f_header.description,"");
    f_header.num_nodes = nodes.size();
    f_header.num_edges = edge.size();
    f.write((char*)&f_header, sizeof(header));



    //save nodes
    QHash< node_id, shared_ptr<const FeatureAbstract> >::iterator nodes_iter;
    //char buffer[50];
    for(nodes_iter=nodes.begin(); nodes_iter!=nodes.end();nodes_iter++ ){
        f.write( (char*)&nodes_iter.key(), sizeof(node_id) );
        int type = (nodes_iter.value())->getType();
        f.write( (char*)&type, sizeof(int) );
        nodes_iter.value()->WriteToStream(stream);
    }

    //save edges links
    QSet<edge_id> writed;
     QHash< node_id, QHash<node_id, edge_id>>::iterator from_iter;
     QHash<node_id, edge_id>::iterator to_iter;
    for(from_iter = edges.begin(); from_iter!=edges.end();from_iter++){
        for(to_iter = from_iter->begin(); to_iter!=from_iter->end();to_iter++){
            if(!writed.contains(to_iter.value())){
                f.write((char*)&from_iter.key(), sizeof(node_id));
                f.write((char*)&to_iter.key(), sizeof(node_id));
                f.write((char*)&to_iter.value(), sizeof(edge_id));
                f.write((char*)&edge[to_iter.value()], sizeof(Link));
                writed.insert(to_iter.value());
            }
        }
    }



    f.close();

}

void FeaturesComplexNetwork::load(const char *filename, QList<FeatureFactoryAbstract*> featuresConstructors){
    clear();
    QFile f(filename);
    f.open(QIODevice::ReadOnly);
    QDataStream stream(&f);

     header f_header;

    current_node_id = 0;
    f.read( (char*)&f_header, sizeof(header) );
    //printf("%u\n", file_header.num_nodes);
    //printf("%u\n", file_header.num_edges);

    //load nodes
    for( unsigned int n = 0; n < f_header.num_nodes; n++ ){
        node_id id;
        f.read( (char*)&id, sizeof(node_id) );
        int type;
        f.read( (char*)&type, sizeof(int) );
        FeatureAbstract *feature = NULL;
        foreach(FeatureFactoryAbstract* constructor, featuresConstructors ){
            if(constructor->getType() == type){
                feature = constructor->CreateFromStream(stream);
                break;
            }
        }
        assert(feature!=NULL);
        nodes.insert(id, shared_ptr<const FeatureAbstract>(feature));

        if(id >= current_node_id)
            current_node_id = id+1;
    }

    //load edges links
    for(unsigned int e = 0; e < f_header.num_edges; e++){
        node_id from, to;
        edge_id edgeid;
        Link edge_value;
        f.read((char*)&(from), sizeof(node_id));
        f.read((char*)&(to), sizeof(node_id));
        f.read((char*)&(edgeid), sizeof(edge_id));
        f.read((char*)&(edge_value), sizeof(Link));
        edges[from].insert(to, edgeid);
        edges[to].insert(from, edgeid);
        edge.insert(edgeid, edge_value);
    }


    f.close();
}

void FeaturesComplexNetwork::clear(){

     /*QHash<node_id, shared_ptr<const FeatureAbstract*> >::iterator nodes_iter;
    for(nodes_iter=nodes.begin(); nodes_iter!=nodes.end();nodes_iter++){
        delete *nodes_iter;
    }*/
    nodes.clear();
    edges.clear();
    edge.clear();
    current_node_id=0;
    current_edge_id=0;
}

FeaturesComplexNetwork::~FeaturesComplexNetwork(){
    //clear();
}

float FeaturesComplexNetwork::getOutputDegree(node_id from) const{
    float total=0;
    for(auto e = edges[from].begin(); e!=edges[from].end();e++){
        total += edge[e.value()].getWeight();
    }
    return total;
}

/*
bool FeaturesComplexNetwork::removeNode(node_id id){
    assert(getNode(id));
    //delete (*getNode(id));
    return ComplexNetwork<shared_ptr<const FeatureAbstract*>, Link>::removeNode(id);
}*/

void FeaturesComplexNetwork::updateIndex(){
    featureIndex.clear();
    //char buffer[100];
    for(auto i = Begin(); i!=End();i++){
        //printf("%s\n", (*i)->asString(buffer) );
        featureIndex[FeatureAbstractKey( i->get() )] = i.getNodeId();
    }
}

node_id FeaturesComplexNetwork::getNodeFromFeature(const FeatureAbstract *f) const{
    if(featureIndex.contains(FeatureAbstractKey(f))){
        return featureIndex[FeatureAbstractKey(f)];
    }
    return -1;
}

QList<node_id> FeaturesComplexNetwork::getNodesOfSameLabel(node_id id) {
    QList<node_id> ret;
    for(auto e = EdgesBegin(id); e != EdgesEnd(id); e++){
        if(e->isSameLabel()){
            ret.append(e.getToNodeId());
        }
    }
    return ret;
}

