#ifndef COMPLEXNETWORK_HPP
#define COMPLEXNETWORK_HPP

#include <QHash>
#include <QPair>
#include <QMap>
#include <QFile>

typedef unsigned int node_id;
typedef unsigned int edge_id;

template <typename NODE_TYPE, typename EDGE_TYPE>
class ComplexNetwork
{
protected:
    node_id current_node_id;
    QHash< node_id, NODE_TYPE> nodes;
    QHash< QPair< node_id, node_id>, EDGE_TYPE > edges;
    QPair<node_id, node_id> createEdgeKey(node_id from, node_id to);
    struct{
        char description[200];
        unsigned int num_nodes;
        unsigned int num_edges;
    }file_header;


public:
    ComplexNetwork();
    node_id addNode(const NODE_TYPE& n);
    NODE_TYPE* getNode(node_id id);
    bool removeNode(node_id id);
    void addEdge(node_id from, node_id to, const EDGE_TYPE& e);
    EDGE_TYPE* getEdge(node_id from, node_id to);
    bool removeEdge(node_id from, node_id to);
    class NodeIterator{
        friend class ComplexNetwork<NODE_TYPE, EDGE_TYPE>;
    private:
        typename QHash< node_id, NODE_TYPE>::iterator iter;
        NodeIterator(typename QHash< node_id, NODE_TYPE>::iterator iter):iter(iter){}

    public:
        NODE_TYPE& operator*(){
            return iter.value();
        }
        NODE_TYPE* operator->(){
            return &iter.value();
        }
        NodeIterator & operator++(){
            this->iter++;
            return *this;
        }
        NodeIterator & operator++(int i){
            this->iter++;
            return *this;
        }
        NodeIterator & operator--(){
            this->iter--;
            return *this;
        }
        bool operator!=(const NodeIterator& other) const{
            return (this->iter != other.iter);
        }


        node_id getNodeId() const{
            return iter.key();
        }
    };

    NodeIterator Begin();
    NodeIterator End();

    void save(const char * filename);
    void load(const char * filename);

};

template <typename NODE_TYPE, typename EDGE_TYPE>
ComplexNetwork<NODE_TYPE, EDGE_TYPE>::ComplexNetwork():current_node_id(0){

}

template <typename NODE_TYPE, typename EDGE_TYPE>
inline QPair<node_id, node_id> ComplexNetwork<NODE_TYPE, EDGE_TYPE>::createEdgeKey(node_id from, node_id to){
    //TODO: directed and undirected network
    //if undirected:
    node_id f = from < to ? from : to;
    node_id t = from < to ? to : from;
    return QPair<node_id, node_id>(f,t);
}

template <typename NODE_TYPE, typename EDGE_TYPE>
node_id ComplexNetwork<NODE_TYPE, EDGE_TYPE>::addNode(const NODE_TYPE& n){
    node_id new_node_id = current_node_id;
    current_node_id++;
    nodes.insert(new_node_id, n);
    return new_node_id;
}

template <typename NODE_TYPE, typename EDGE_TYPE>
NODE_TYPE* ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getNode(node_id id){
    if(nodes.contains(id))
        return &nodes[id];
    return NULL;
}

template <typename NODE_TYPE, typename EDGE_TYPE>
bool ComplexNetwork<NODE_TYPE, EDGE_TYPE>::removeNode(node_id id){
    return nodes.remove(id) > 0;
}

template <typename NODE_TYPE, typename EDGE_TYPE>
void ComplexNetwork<NODE_TYPE, EDGE_TYPE>::addEdge(node_id from, node_id to, const EDGE_TYPE &e){
    edges.insert(createEdgeKey(from, to), e);
}

template <typename NODE_TYPE, typename EDGE_TYPE>
EDGE_TYPE* ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getEdge(node_id from, node_id to){
    if(edges.contains(createEdgeKey(from, to)))
        return &edges[createEdgeKey(from, to)];
    return NULL;
}

template <typename NODE_TYPE, typename EDGE_TYPE>
bool ComplexNetwork<NODE_TYPE, EDGE_TYPE>::removeEdge(node_id from, node_id to){
    return edges.remove(from, to)>0;
}


template <typename NODE_TYPE, typename EDGE_TYPE>
void ComplexNetwork<NODE_TYPE, EDGE_TYPE>::save(const char* filename){
    QFile f(filename);
    f.open(QIODevice::WriteOnly);

    strcpy(file_header.description,"");
    file_header.num_nodes = nodes.size();
    file_header.num_edges = edges.size();
    f.write((char*)&file_header, sizeof(file_header));

    //save nodes
    typename QHash< node_id, NODE_TYPE>::iterator nodes_iter;
    for(nodes_iter=nodes.begin(); nodes_iter!=nodes.end();nodes_iter++ ){
        f.write( (char*)&nodes_iter.key(), sizeof(node_id) );
        f.write( (char*)&(nodes_iter.value()), sizeof(NODE_TYPE) );
    }

    //save edges
    typename QHash< QPair< node_id, node_id>, EDGE_TYPE >::iterator edges_iter;
    for(edges_iter = edges.begin(); edges_iter!=edges.end();edges_iter++){
        f.write((char*)&edges_iter.key().first, sizeof(node_id));
        f.write((char*)&edges_iter.key().second, sizeof(node_id));
        f.write((char*)&edges_iter.value(), sizeof(EDGE_TYPE));
    }


    f.close();
}


template <typename NODE_TYPE, typename EDGE_TYPE>
void ComplexNetwork<NODE_TYPE, EDGE_TYPE>::load(const char* filename){
    QFile f(filename);
    f.open(QIODevice::ReadOnly);

    current_node_id = 0;
    f.read( (char*)&file_header, sizeof(file_header) );

    //save nodes
    for( unsigned int n = 0; n < file_header.num_nodes; n++ ){
        node_id id;
        NODE_TYPE node;
        f.read( (char*)&id, sizeof(node_id) );
        f.read( (char*)&(node), sizeof(NODE_TYPE) );
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

}


template <typename NODE_TYPE, typename EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::NodeIterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::Begin(){
    return typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::NodeIterator(nodes.begin());
}

template <typename NODE_TYPE, typename EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::NodeIterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::End(){
    return typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::NodeIterator(nodes.end());
}
#endif // COMPLEXNETWORK_HPP






