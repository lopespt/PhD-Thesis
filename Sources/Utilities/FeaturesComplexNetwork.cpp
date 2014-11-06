#include "FeaturesComplexNetwork.hpp"
#include <string.h>

FeaturesComplexNetwork::FeaturesComplexNetwork():ComplexNetwork()
{
}

void FeaturesComplexNetwork::save(const char* filename){
    file_header.num_nodes = this->nodes.size();
    file_header.num_edges = this->edges.size();
    strcpy(file_header.description, "");

    QFile f(filename);
    f.open(QIODevice::WriteOnly);

    strcpy(file_header.description,"");
    file_header.num_nodes = nodes.size();
    file_header.num_edges = edges.size();
    f.write((char*)&file_header, sizeof(file_header));

    //save nodes
    typename QHash< node_id, const FeatureAbstract*>::iterator nodes_iter;
    char buffer[50];
    for(nodes_iter=nodes.begin(); nodes_iter!=nodes.end();nodes_iter++ ){
        f.write( (char*)&nodes_iter.key(), sizeof(node_id) );
        f.write( nodes_iter.value()->asString(buffer), 50);
        f.write( (char*)&(nodes_iter.value()->data_size), sizeof(nodes_iter.value()->data_size) );
        f.write( (char*)&(nodes_iter.value()->data), nodes_iter.value()->data_size );
    }

    //save edges
    typename QHash< QPair< node_id, node_id>, Link >::iterator edges_iter;
    for(edges_iter = edges.begin(); edges_iter!=edges.end();edges_iter++){
        f.write((char*)&edges_iter.key().first, sizeof(node_id));
        f.write((char*)&edges_iter.key().second, sizeof(node_id));
        f.write((char*)&edges_iter.value(), sizeof(Link));
    }


    f.close();

}

void FeaturesComplexNetwork::load(const char *filename, QList<FeatureAbstract*> featuresConstructors){
    /*
    QFile f(filename);
    f.open(QIODevice::ReadOnly);

    current_node_id = 0;
    f.read( (char*)&file_header, sizeof(file_header) );

    //save nodes
    for( unsigned int n = 0; n < file_header.num_nodes; n++ ){
        node_id id;
        f.write( (char*)&id, sizeof(node_id) );
        char buffer[50];
        //f.read()
        f.write((char*)&(node), sizeof(NODE_TYPE) );
        nodes.insert(id, node);


        if(id >= current_node_id)
            current_node_id = id+1;
    }

    //save edges
    typename QHash< QPair< node_id, node_id>, EDGE_TYPE >::iterator edges_iter;
    for(edges_iter = edges.begin(); edges_iter!=edges.end();edges_iter++){
        node_id from, to;
        EDGE_TYPE edge;
        f.write((char*)&(from), sizeof(node_id));
        f.write((char*)&(to), sizeof(node_id));
        f.write((char*)&(edge), sizeof(EDGE_TYPE));
        edges.insert(createEdgeKey(from, to), edge);
    }


    f.close();
    */
}
