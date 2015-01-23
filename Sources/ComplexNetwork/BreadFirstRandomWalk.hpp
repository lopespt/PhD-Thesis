#ifndef BREADFIRSTRANDOMWALK_HPP
#define BREADFIRSTRANDOMWALK_HPP

#include "ComplexNetwork.hpp"
#include <stdlib.h>
#include <set>
#include <vector>

using namespace std;
template <class NODE_TYPE, class EDGE_TYPE, class ProbabilityGetter>
class BreadFirstRandomWalk
{
private:
    ComplexNetwork<NODE_TYPE, EDGE_TYPE> *cn;
    vector<float> probab;

public:
    BreadFirstRandomWalk(ComplexNetwork<NODE_TYPE, EDGE_TYPE> *cn);
    void Execute(node_id start_node, int maxSteps = -1);
    float getProbability(node_id);
};


template <class NODE_TYPE, class EDGE_TYPE, class ProbabilityGetter>
BreadFirstRandomWalk<NODE_TYPE, EDGE_TYPE, ProbabilityGetter>::BreadFirstRandomWalk(ComplexNetwork<NODE_TYPE, EDGE_TYPE> *cn):
    cn(cn), probab(cn->getNumNodes()){
    for(int i=0;i<probab.size();i++){
        probab[i] = 0; //Set prob to 0 for all nodes
    }
}


template <class NODE_TYPE, class EDGE_TYPE, class ProbabilityGetter>
void BreadFirstRandomWalk<NODE_TYPE, EDGE_TYPE, ProbabilityGetter>::Execute(node_id start_node, int maxSteps){
    srand(time(NULL));
    typedef ComplexNetwork<NODE_TYPE, EDGE_TYPE> cn_type;
    ProbabilityGetter getWeigth;
    typedef struct{
        node_id id;
        float priority;
    }queue_t;
    vector<queue_t> queue;
    set<node_id> explored;

    queue.push_back({start_node, 0});
    probab[start_node] = 1;
    unsigned int steps = 0;
    explored.insert(start_node);
    while(!queue.empty() && (steps < maxSteps || maxSteps==-1)){
        node_id node = queue[0].id;
        pop_heap(queue.begin(), queue.end(),[&](const queue_t& a, const queue_t &b){return a.priority > b.priority;});
        queue.pop_back();
        explored.insert(node);
        for(typename cn_type::EdgeIterator e = cn->EdgesBegin(node); e != cn->EdgesEnd(node); e++){
            if(explored.find(e.getToNodeId()) == explored.end() ){
                float prob = getWeigth(cn, e.getEdgeId());
                probab[e.getToNodeId()] += probab[node]*prob;
                queue.push_back({e.getToNodeId(), steps+probab[e.getToNodeId()] });
                push_heap(queue.begin(), queue.end(), [&](const queue_t& a, const queue_t &b){return a.priority > b.priority;});
            }
            //explored.insert(e.getToNodeId());
        }
        steps++;
    }
}

template <class NODE_TYPE, class EDGE_TYPE, class ProbabilityGetter>
float BreadFirstRandomWalk<NODE_TYPE, EDGE_TYPE, ProbabilityGetter>::getProbability(node_id id){
    return probab[id];
}

#endif // BREADFIRSTRANDOMWALK_HPP
