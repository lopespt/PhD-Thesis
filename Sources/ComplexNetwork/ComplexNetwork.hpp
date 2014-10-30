
#ifndef COMPLEX_NETWORK__CPP
#define COMPLEX_NETWORK__CPP


#include <list>
#include <algorithm>
#include <map>
#include <cstring>
#include "Node.hpp"
#include "Edge.hpp"
#include <assert.h>

/** \brief Rede Complexa
 *  \details Rede Complexa utilizando listas de adjacências
 * **/


template <class NODE_TYPE, class EDGE_TYPE>
class ComplexNetwork{
    public:
        typedef Node<NODE_TYPE, EDGE_TYPE>* NodePtr;
        typedef Edge<NODE_TYPE, EDGE_TYPE> * EdgePtr;
        typedef typename std::multimap< std::pair< NodePtr, NodePtr>, EdgePtr>::iterator edge_iterator;
        typedef typename std::map<NODE_TYPE, NodePtr>::iterator node_iterator;

    private:

        std::map<NODE_TYPE, NodePtr> nodes;
        std::multimap< std::pair< NodePtr, NodePtr>, EdgePtr, 
           bool(*)(std::pair<NodePtr, NodePtr> , std::pair<NodePtr, NodePtr>) > edges;
        static bool compare(std::pair< NodePtr, NodePtr> a, std::pair< NodePtr, NodePtr> b);

        //Type for save and load ComplexNetwork
        typedef struct{
            unsigned int ComplexNetworkFileVersion;
            unsigned long long int num_nodes;
            unsigned long long int num_edges;
        }ComplexNetwordFileHeader;
        typedef struct{
            unsigned long long int node_from;
            unsigned long long int node_to;
            char value[sizeof(EDGE_TYPE)];
        }edge_data_type;
        typedef struct{
            unsigned long long int id;
            char value[sizeof(NODE_TYPE)];
        }node_data_type;



    public:
        ComplexNetwork();
        virtual ~ComplexNetwork();


        void addNode(NodePtr);
        void addEdge(EdgePtr);
        EdgePtr getEdge(NodePtr, NodePtr);
        NodePtr getNode(NODE_TYPE);
        node_iterator getNodesBeginIterator();
        node_iterator getNodesEndIterator();
        edge_iterator getEdgesBeginIterator();
        edge_iterator getEdgesEndIterator();
        edge_iterator getEdgesFromNode_LowerBound(NodePtr n);
        edge_iterator getEdgesFromNode_UpperBound(NodePtr n);
        unsigned long int getNodesCount() const;
        unsigned long int getEdgesCount() const;
        void save(const char *filename) const;
        void load(const char *filename);
        void clear();


};


template <class NODE_TYPE, class EDGE_TYPE>
ComplexNetwork<NODE_TYPE,EDGE_TYPE>::ComplexNetwork():edges( ComplexNetwork<NODE_TYPE, EDGE_TYPE>::compare ){
}


template <class NODE_TYPE, class EDGE_TYPE>
void ComplexNetwork<NODE_TYPE,EDGE_TYPE>::addNode(NodePtr n){
    if (this->nodes.find(n->getAttribute()) == this->nodes.end())
        this->nodes[n->getAttribute()]=n;
    else 
        delete n;
}

template <class NODE_TYPE, class EDGE_TYPE>
void ComplexNetwork<NODE_TYPE,EDGE_TYPE>::addEdge(EdgePtr e){
    std::pair< std::pair<NodePtr, NodePtr>, EdgePtr > v;
    v.first = std::pair<NodePtr, NodePtr>(e->from, e->to);
    v.second = e;
    if(edges.find(v.first) == edges.end())
        edges.insert(v);
    else
        delete e;

}

template <class NODE_TYPE, class EDGE_TYPE>
ComplexNetwork<NODE_TYPE, EDGE_TYPE>::~ComplexNetwork(){
    //clear();
}


template <class NODE_TYPE, class EDGE_TYPE>
bool ComplexNetwork<NODE_TYPE, EDGE_TYPE>::compare(std::pair< NodePtr, NodePtr> a, std::pair< NodePtr, NodePtr> b){
    NodePtr a1 = a.first > a.second ? a.first : a.second;
    NodePtr a2 = a.first > a.second ? a.second : a.first;
    NodePtr b1 = b.first > b.second ? b.first : b.second;
    NodePtr b2 = b.first > b.second ? b.second : b.first;
    if(a2 == NULL || b2 == NULL)
        return b1>a1;

    if(b1 != a1)
       return b1>a1;
    return b2>a2;
}


template <class NODE_TYPE, class EDGE_TYPE>
Edge<NODE_TYPE, EDGE_TYPE>* ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getEdge(NodePtr a, NodePtr b){
   auto e= edges.find(std::pair<NodePtr, NodePtr>(a, b));
   if(e != edges.end())
       return e->second;
   else 
       return NULL;
}


template <class NODE_TYPE, class EDGE_TYPE>
Node<NODE_TYPE, EDGE_TYPE>* ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getNode(NODE_TYPE attribute){
   auto n = nodes.find(attribute);
   if(n != nodes.end())
       return n->second;
   else 
       return NULL;
}



template <class NODE_TYPE, class EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::node_iterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getNodesBeginIterator(){
    return nodes.begin();
}

template <class NODE_TYPE, class EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::node_iterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getNodesEndIterator(){
    return nodes.end();
}

template <class NODE_TYPE, class EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::edge_iterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getEdgesBeginIterator(){
    return edges.begin();
}

template <class NODE_TYPE, class EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::edge_iterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getEdgesEndIterator(){
    return edges.end();
}

template <class NODE_TYPE, class EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::edge_iterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getEdgesFromNode_LowerBound(NodePtr n){
    return edges.lower_bound( std::pair<NodePtr, NodePtr>(n, NULL) );
}

template <class NODE_TYPE, class EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::edge_iterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getEdgesFromNode_UpperBound(NodePtr n){
    return edges.upper_bound( std::pair<NodePtr, NodePtr>(n, NULL) );
}


template <class NODE_TYPE, class EDGE_TYPE>
unsigned long int ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getNodesCount() const{
    return this->nodes.size();
}

/**
 * Retorna o numero de arestas do grafo
 */
template <class NODE_TYPE, class EDGE_TYPE>
unsigned long int ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getEdgesCount() const{
    return this->edges.size();
}


template <class NODE_TYPE, class EDGE_TYPE>
void ComplexNetwork<NODE_TYPE, EDGE_TYPE>::save(const char *filename) const{
    unsigned long long int last_id = 0ull;
    std::map< NodePtr, unsigned long long int> ids;
    ComplexNetwordFileHeader header;
    header.ComplexNetworkFileVersion = 1;
    header.num_nodes = this->getNodesCount();
    header.num_edges = this->getEdgesCount();

    node_data_type node_data;
    edge_data_type edge_data;

    FILE* f = fopen(filename, "wb");

    //Save the header
    fwrite(&header,sizeof(ComplexNetwordFileHeader), 1, f);


    for(auto n=this->nodes.begin(); n != this->nodes.end(); n++){
        node_data.id = last_id;
        memcpy(node_data.value, &(n->second->attribute), sizeof(NODE_TYPE));
        ids[n->second] = last_id;
        fwrite(&node_data, sizeof(node_data_type), 1, f);
        last_id++;
    }


    for(auto e = this->edges.begin(); e != this->edges.end(); e++){
        edge_data.node_from = ids.find(e->second->from)->second;
        edge_data.node_to = ids.find(e->second->to)->second;
        memcpy(edge_data.value, &(e->second->attribute), sizeof(EDGE_TYPE));
        fwrite(&edge_data, sizeof(edge_data_type), 1, f);
    }

    fclose(f);
}

template <class NODE_TYPE, class EDGE_TYPE>
void ComplexNetwork<NODE_TYPE, EDGE_TYPE>::load(const char *filename){
    clear();
    std::map< unsigned long long int, NodePtr> ids;
    ComplexNetwordFileHeader header;
    int leitura_ok;

    NodePtr newNode;
    EdgePtr newEdge;
    FILE* f = fopen(filename, "rb");
    leitura_ok = fread(&header, sizeof(header), 1, f);
    assert(leitura_ok==1);

    node_data_type node_data;
    edge_data_type edge_data;


    //Read Nodes
    for(int i=0;i<header.num_nodes;i++){
        leitura_ok = fread(&node_data, sizeof(node_data), 1, f);
        assert(leitura_ok==1);
        newNode = new Node<NODE_TYPE, EDGE_TYPE>;
        memcpy(&(newNode->attribute), node_data.value, sizeof(NODE_TYPE));
        this->addNode(newNode);
        ids[node_data.id] = newNode;
    }

    for(int i=0;i<header.num_edges;i++){
        leitura_ok = fread(&edge_data, sizeof(edge_data), 1, f);
        assert(leitura_ok==1);
        newEdge = new Edge<NODE_TYPE, EDGE_TYPE>;
        memcpy(&(newEdge->attribute), edge_data.value, sizeof(EDGE_TYPE));
        newEdge->from = ids[edge_data.node_from];
        newEdge->to = ids[edge_data.node_to];
        this->addEdge(newEdge);
    }


}

template <class NODE_TYPE, class EDGE_TYPE>
void ComplexNetwork<NODE_TYPE, EDGE_TYPE>::clear(){
    std::for_each(this->edges.begin(), this->edges.end(),
            []( std::pair< std::pair<NodePtr, NodePtr>,  EdgePtr > el ){
                delete el.second;
            });

    edges.clear();


    std::for_each(nodes.begin(), nodes.end(),
            [](std::pair< NODE_TYPE, NodePtr> el){
                delete el.second;
            });

    nodes.clear();

}

#endif




