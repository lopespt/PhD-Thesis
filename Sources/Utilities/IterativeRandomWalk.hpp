#ifndef ITERATIVERANDOMWALK_HPP
#define ITERATIVERANDOMWALK_HPP

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/CachedComplexNetwork.hpp>
#include "RandomWalk.hpp"
#include <stdlib.h>
#include <vector>
#include <set>
using namespace std;
class IterativeRandomWalk
{
private:
    CachedComplexNetwork<int, double> cn;
    vector<double> probs;
    vector<double> probs2;
    typedef struct{
        node_id from;
        node_id to;
    }edges_list;

public:
    IterativeRandomWalk(FeaturesComplexNetwork *cn);
    void Execute(node_id start_node, unsigned int max_path_length);
    float getProbability(node_id node);
};


IterativeRandomWalk::IterativeRandomWalk(FeaturesComplexNetwork *cn):
    cn(cn),probs(cn->getNumNodes()){
    for(int i=0;i<probs.size();i++)
        probs[i] = 0;
   this->cn = RandomWalk::convertToWalkNetwork(*cn);
   this->cn = RandomWalk::addAutoLoop(this->cn);
   this->cn = RandomWalk::normalizeGraph(this->cn);
}

void IterativeRandomWalk::Execute(node_id start_node, unsigned int max_path_length){
    for(int i=0;i<probs.size();i++)
        probs[i] = 0;
    probs[start_node] = 1;

    for(int i=0; i<max_path_length; i++){
        probs2 = probs;
        for(auto node = cn.Begin(); node != cn.End(); node++){
            double probSum = 0;
            for(auto edge=node.EdgesBegin(); edge != node.EdgesEnd(); edge++){
                probSum += probs[ *cn.getNode(edge.getToNodeId())] * (*cn.getEdge(edge.getToNodeId(),  edge.getFromNodeId() ));
            }
            probs2[*node] = probSum;
        }
        probs = probs2;
    }
}

float IterativeRandomWalk::getProbability(node_id node){
    return probs[node];
}

#endif // ITERATIVERANDOMWALK_HPP
