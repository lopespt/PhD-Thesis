#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "ComplexNetwork.hpp"
#include <type_traits>
#include <stdlib.h>

using namespace std;
template <class NODE_TYPE, class EDGE_TYPE, class DistanceGetter>
class Dijkstra
{
private:
    ComplexNetwork<NODE_TYPE, EDGE_TYPE> *cn;
    vector<float> distances;

public:
    Dijkstra(ComplexNetwork<NODE_TYPE, EDGE_TYPE> *cn);
    void Execute(node_id start_node, int maxSteps = -1);
    float getDistance(node_id);
};

template <class NODE_TYPE, class EDGE_TYPE, class DistanceGetter>
Dijkstra<NODE_TYPE, EDGE_TYPE, DistanceGetter>::Dijkstra(ComplexNetwork<NODE_TYPE, EDGE_TYPE> *cn):cn(cn),distances(cn->getNumNodes()){
    for(int i=0;i < distances.size();i++){
        distances[i] = -1; //Set to -inf
    }
}


template <class NODE_TYPE, class EDGE_TYPE, class DistanceGetter>
void Dijkstra<NODE_TYPE, EDGE_TYPE, DistanceGetter>::Execute(node_id start_node, int maxSteps){
    typedef ComplexNetwork<NODE_TYPE, EDGE_TYPE> cn_type;
    DistanceGetter getWeight;
    vector<node_id> queue;
    vector<char> explored;

    explored.resize(cn->getNumNodes());
    for(int i=0;i<explored.size();i++){
        explored[i] = 0;
    }

    queue.push_back(start_node);
    distances[start_node] = 0;
    unsigned int steps = 0;
    while(!queue.empty() && (steps < maxSteps || maxSteps==-1)){
        node_id node = queue.front();
        pop_heap(queue.begin(), queue.end());
        queue.pop_back();
        for(typename cn_type::EdgeIterator e = cn->EdgesBegin(node); e != cn->EdgesEnd(node); e++){

            float dist = getWeight(cn, e.getEdgeId());
            //Relaxamento
            if( distances[e.getToNodeId()] == -1 || distances[e.getToNodeId()] > distances[node] + dist ){
                distances[e.getToNodeId()] = distances[node] + dist;
            }
            if(!explored[e.getToNodeId()]){
                queue.push_back(e.getToNodeId());
                push_heap(queue.begin(), queue.end(), [&](const node_id& a, const node_id &b){return (distances[a] > distances[b]) || (distances[a] == -1);});
            }
        }
        explored[node] = 1;
        steps++;
    }
}

template <class NODE_TYPE, class EDGE_TYPE, class DistanceGetter>
float Dijkstra<NODE_TYPE, EDGE_TYPE, DistanceGetter>::getDistance(node_id id){
    return distances[id];
}

#endif // DIJKSTRA_HPP
