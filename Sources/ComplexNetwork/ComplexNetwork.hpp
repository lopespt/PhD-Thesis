#ifndef COMPLEXNETWORK_HPP
#define COMPLEXNETWORK_HPP

#include <QHash>
#include <QPair>
#include <QMap>
#include <QFile>
#include <QSet>
#include <assert.h>

typedef unsigned int node_id;
typedef unsigned int edge_id;

template <typename NODE_TYPE, typename EDGE_TYPE>
class ComplexNetwork
{
protected:
    node_id current_node_id;
    edge_id current_edge_id;
    bool directed;
    QHash< node_id, NODE_TYPE> nodes;
    QHash< node_id, QHash<node_id, edge_id> > edges;
    QHash< edge_id, EDGE_TYPE> edge;
    QPair<node_id, node_id> createEdgeKey(node_id from, node_id to);
    struct{
        char description[200];
        unsigned int num_nodes;
        unsigned int num_edges;
    }file_header;


public:
    ComplexNetwork(bool directed=false);
    virtual node_id addNode(const NODE_TYPE& n);
    virtual NODE_TYPE* getNode(node_id id);
    virtual bool removeNode(node_id id);
    virtual void addEdge(node_id from, node_id to, const EDGE_TYPE& e);
    virtual EDGE_TYPE* getEdge(node_id from, node_id to);
    virtual bool removeEdge(node_id from, node_id to);
    virtual void clear();
    unsigned int getNumNodes() const;
    unsigned int getNumEdges() const;


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
        bool operator==(const NodeIterator& other) const{
            return (this->iter == other.iter);
        }


        node_id getNodeId() const{
            return iter.key();
        }

    };

    class EdgeIterator{
        friend class ComplexNetwork<NODE_TYPE, EDGE_TYPE>;
    private:
        typename QHash<node_id, edge_id>::iterator iter;
        typename QHash<edge_id, EDGE_TYPE>::iterator iter2;
        ComplexNetwork<NODE_TYPE, EDGE_TYPE>* cn;
        bool allEdges=false;

        EdgeIterator(ComplexNetwork<NODE_TYPE, EDGE_TYPE> *cn, typename QHash<node_id, edge_id>::iterator iter):iter(iter),cn(cn), allEdges(false){}
        EdgeIterator(typename QHash<edge_id, EDGE_TYPE>::iterator iter2):iter2(iter2), allEdges(true){}

     public:
        EDGE_TYPE& operator*(){
            if(allEdges){
                return iter2.value();
            }
            assert(cn->edge.contains(iter.value()));
            return cn->edge[iter.value()];
        }
        EDGE_TYPE* operator->(){
            if(allEdges)
                return &iter2.value();
            return &cn->edge[iter.value()];
        }
        EdgeIterator & operator++(){
            if(allEdges)
                this->iter2++;
            this->iter++;
            return *this;
        }
        EdgeIterator & operator++(int i){
            if(allEdges)
                this->iter2++;
            this->iter++;
            return *this;
        }
        EdgeIterator & operator--(){
            if(allEdges)
                this->iter2--;
            this->iter--;
            return *this;
        }
        bool operator!=(const EdgeIterator& other) const{
            if(allEdges)
                return (this->iter2 != other.iter2);
            return (this->iter != other.iter);
        }
        bool operator==(const EdgeIterator& other) const{
            if(allEdges)
                return (this->iter2 == other.iter2);
            return (this->iter == other.iter);
        }


        edge_id getEdgeId() const{
            if(allEdges)
                return iter2.key();
            return iter.value();
        }

        node_id getToNodeId() const{
            assert(allEdges==false);
            return iter.key();
        }

    };


    NodeIterator Begin();
    NodeIterator End();
    EdgeIterator EdgesBegin(node_id node_from);
    EdgeIterator EdgesEnd(node_id node_from);
    EdgeIterator EdgesBegin();
    EdgeIterator EdgesEnd();

    unsigned int getNumEdges(node_id) const;


    void save(const char * filename);
    void load(const char * filename);

};

template <typename NODE_TYPE, typename EDGE_TYPE>
ComplexNetwork<NODE_TYPE, EDGE_TYPE>::ComplexNetwork(bool directed):current_node_id(0), current_edge_id(0), directed(directed){

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
    QList<QPair<node_id, node_id>> del;
    for(auto e = edges[id].begin(); e !=  edges[id].end(); e++){
        del.append(QPair<node_id, node_id>(id, e.key()));
    }
    foreach(auto i, del){
        removeEdge(i.first, i.second);
    }

    return nodes.remove(id) > 0;
}

template <typename NODE_TYPE, typename EDGE_TYPE>
void ComplexNetwork<NODE_TYPE, EDGE_TYPE>::addEdge(node_id from, node_id to, const EDGE_TYPE &e){
    edge_id new_edge_id = current_edge_id;
    current_edge_id++;
    edge.insert(new_edge_id, e);

    edges[from][to] = new_edge_id;
    if(!directed){
        edges[to][from] = new_edge_id;
    }
}

template <typename NODE_TYPE, typename EDGE_TYPE>
EDGE_TYPE* ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getEdge(node_id from, node_id to){
    if(edges.contains(from) && edges[from].contains(to))
        return &edge[edges[from][to]];
    return NULL;
}

template <typename NODE_TYPE, typename EDGE_TYPE>
bool ComplexNetwork<NODE_TYPE, EDGE_TYPE>::removeEdge(node_id from, node_id to){
    if(edges[from].contains(to)){
        if(edge.contains(edges[from][to]))
            edge.remove(edges[from][to]);
    }

    if (!directed){
        if(edges[to].contains(from))
            edges.remove(edges[to][from]);
        return edges[from].remove(to) && edges[to].remove(from) > 0;
    }

    return edges[from].remove(to)>0;
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

    //save edges links
    typename QHash< node_id, QHash<node_id, edge_id>>::iterator from_iter;
    typename QHash<node_id, edge_id>::iterator to_iter;
    for(from_iter = edges.begin(); from_iter!=edges.end();from_iter++){
        for(to_iter = from_iter->begin(); to_iter!=from_iter->end();to_iter++){
            f.write((char*)&from_iter.key(), sizeof(node_id));
            f.write((char*)&to_iter.key(), sizeof(node_id));
            f.write((char*)&to_iter.value(), sizeof(edge_id));
            f.write((char*)&edge[to_iter.value()].value(), sizeof(EDGE_TYPE));
        }
    }


    f.close();
}


template <typename NODE_TYPE, typename EDGE_TYPE>
void ComplexNetwork<NODE_TYPE, EDGE_TYPE>::load(const char* filename){
    QFile f(filename);
    f.open(QIODevice::ReadOnly);

    current_node_id = 0;
    f.read( (char*)&file_header, sizeof(file_header) );

    //load nodes
    for( unsigned int n = 0; n < file_header.num_nodes; n++ ){
        node_id id;
        NODE_TYPE node;
        f.read( (char*)&id, sizeof(node_id) );
        f.read( (char*)&(node), sizeof(NODE_TYPE) );
        nodes.insert(id, node);
        if(id >= current_node_id)
            current_node_id = id+1;
    }

    //load edges
    typename QHash< QPair< node_id, node_id>, EDGE_TYPE >::iterator edges_iter;
    for(edges_iter = edges.begin(); edges_iter!=edges.end();edges_iter++){
        node_id from, to;
        EDGE_TYPE edge;
        f.read((char*)&(from), sizeof(node_id));
        f.read((char*)&(to), sizeof(node_id));
        f.read((char*)&(edge), sizeof(EDGE_TYPE));
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

template <typename NODE_TYPE, typename EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgeIterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgesBegin(node_id node_from){
    //assert(edges.contains(node_from));
    return typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgeIterator(this, edges[node_from].begin());
}

template <typename NODE_TYPE, typename EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgeIterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgesEnd(node_id node_from){
    //assert(edges.contains(node_from));
    return typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgeIterator(this, edges[node_from].end());
}

template <typename NODE_TYPE, typename EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgeIterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgesBegin(){
    return edge.begin();
}

template <typename NODE_TYPE, typename EDGE_TYPE>
typename ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgeIterator ComplexNetwork<NODE_TYPE, EDGE_TYPE>::EdgesEnd(){
    return edge.end();
}

template <typename NODE_TYPE, typename EDGE_TYPE>
void ComplexNetwork<NODE_TYPE, EDGE_TYPE>::clear(){
    this->nodes.clear();
    this->edges.clear();
}

template <typename NODE_TYPE, typename EDGE_TYPE>
unsigned int ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getNumNodes() const{
    return nodes.size();
}

template <typename NODE_TYPE, typename EDGE_TYPE>
unsigned int ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getNumEdges() const{
    return edge.size();
}


template <typename NODE_TYPE, typename EDGE_TYPE>
unsigned int ComplexNetwork<NODE_TYPE, EDGE_TYPE>::getNumEdges(node_id id) const{
    return edges[id].size();
}


#endif // COMPLEXNETWORK_HPP






