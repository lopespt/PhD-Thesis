#include "FeaturesComplexNetwork.hpp"
#include <string.h>
#include <QDataStream>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>

FeaturesComplexNetwork::FeaturesComplexNetwork():ComplexNetwork()
{
}

void FeaturesComplexNetwork::save(const char* filename){
    file_header.num_nodes = this->nodes.size();
    file_header.num_edges = this->edges.size();
    strcpy(file_header.description, "");

    QFile f(filename);
    f.open(QIODevice::WriteOnly);
    QDataStream stream(&f);


    strcpy(file_header.description,"");
    file_header.num_nodes = nodes.size();
    file_header.num_edges = edge.size();
    f.write((char*)&file_header, sizeof(file_header));

    //save nodes
    typename QHash< node_id, const FeatureAbstract*>::iterator nodes_iter;
    //char buffer[50];
    for(nodes_iter=nodes.begin(); nodes_iter!=nodes.end();nodes_iter++ ){
        f.write( (char*)&nodes_iter.key(), sizeof(node_id) );
        int type = nodes_iter.value()->getType();
        f.write( (char*)&type, sizeof(int) );
        nodes_iter.value()->WriteToStream(stream);
    }

    //save edges links
    QSet<edge_id> writed;
    typename QHash< node_id, QHash<node_id, edge_id>>::iterator from_iter;
    typename QHash<node_id, edge_id>::iterator to_iter;
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
    QFile f(filename);
    f.open(QIODevice::ReadOnly);
    QDataStream stream(&f);

    current_node_id = 0;
    f.read( (char*)&file_header, sizeof(file_header) );
    printf("%u\n", file_header.num_nodes);
    printf("%u\n", file_header.num_edges);

    //load nodes
    for( unsigned int n = 0; n < file_header.num_nodes; n++ ){
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
        nodes.insert(id, feature);

        if(id >= current_node_id)
            current_node_id = id+1;
    }

    //load edges links
    for(unsigned int e = 0; e < file_header.num_edges; e++){
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

    typename QHash<node_id, const FeatureAbstract*>::iterator nodes_iter;
    for(nodes_iter=nodes.begin(); nodes_iter!=nodes.end();nodes_iter++ ){
        delete *nodes_iter;
    }
    nodes.clear();
    edges.clear();
    edge.clear();
}

FeaturesComplexNetwork::~FeaturesComplexNetwork(){
    clear();
}
