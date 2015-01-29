#ifndef CACHEDCOMPLEXNETWORK_HPP
#define CACHEDCOMPLEXNETWORK_HPP
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <QHash>

template <typename NODE_TYPE, typename EDGE_TYPE>
class CachedComplexNetwork:public ComplexNetwork<NODE_TYPE, EDGE_TYPE>
{
private:
    QHash<NODE_TYPE, node_id> cache;
public:
    CachedComplexNetwork(bool directed=true);
    node_id addNode(const NODE_TYPE &n);
    bool removeNode(node_id id);
    node_id getNodeId(const NODE_TYPE &n);
};

template <typename NODE_TYPE, typename EDGE_TYPE>
CachedComplexNetwork<NODE_TYPE, EDGE_TYPE>::CachedComplexNetwork(bool directed):ComplexNetwork<NODE_TYPE, EDGE_TYPE>(directed)
{
}

template <typename NODE_TYPE, typename EDGE_TYPE>
node_id CachedComplexNetwork<NODE_TYPE, EDGE_TYPE>::addNode(const NODE_TYPE &n){
    node_id id = ComplexNetwork<NODE_TYPE, EDGE_TYPE>::addNode( n);
    this->cache.insert(n, id);
    return id;
}

template <typename NODE_TYPE, typename EDGE_TYPE>
bool CachedComplexNetwork<NODE_TYPE, EDGE_TYPE>::removeNode(node_id id){
    assert(this->getNode(id));
    this->cache.remove( *this->getNode(id) );
    return ComplexNetwork<NODE_TYPE, EDGE_TYPE>::removeNode(id);
}

template <typename NODE_TYPE, typename EDGE_TYPE>
node_id CachedComplexNetwork<NODE_TYPE, EDGE_TYPE>::getNodeId(const NODE_TYPE &n){
    return cache[n];
}
#endif // CACHEDCOMPLEXNETWORK_HPP
