#include "IterativeRandomWalk.hpp"


IterativeRandomWalk::IterativeRandomWalk(FeaturesComplexNetwork *cn):
    probs(cn->getNumNodes()){
    for(int i=0;i<probs.size();i++)
        probs[i] = 0;
   this->cn = RandomWalk::convertToWalkNetwork(*cn);
   //this->cn = RandomWalk::addAutoLoop(this->cn);
   this->cn = RandomWalk::normalizeGraph(this->cn);
}

IterativeRandomWalk::IterativeRandomWalk(CachedComplexNetwork<int, double> *cn):cn(*cn),probs(cn->getNumNodes()+1){

}


void IterativeRandomWalk::Execute(node_id start_node, unsigned int max_path_length){
    probs.fill(0);
    probs2 = probs;
    probs[start_node] = 1;
    for(int i=0; i<max_path_length; i++){
        probs2.fill(0);
        for(auto node = cn.Begin(); node != cn.End(); node++){
            if( probs[*node] ){
                for(auto edge=node.EdgesBegin(); edge != node.EdgesEnd(); edge++){
                    probs2[  *cn.getNode(edge.getToNodeId()) ] += probs[*node] * (*cn.getEdge(node.getNodeId(),  edge.getToNodeId() ));
                }
            }
        }
        probs = probs2;
    }
}

float IterativeRandomWalk::getProbability(node_id node){
    return probs[node];
}

QVector<double> IterativeRandomWalk::getAllProbs(){
    return probs;
}
