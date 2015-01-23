#include "RandomWalk.hpp"
#include "CachedComplexNetwork.hpp"
#include <QHash>

RandomWalk::RandomWalk()
{
}

CachedComplexNetwork<int, double> RandomWalk::walkOneStep(CachedComplexNetwork<int, double> cn){
    CachedComplexNetwork<int, double> res = cn;
    CachedComplexNetwork<int, double>::NodeIterator node;
    CachedComplexNetwork<int, double>::NodeIterator node2;
    CachedComplexNetwork<int, double>::NodeIterator node3;

        //Multiply
        for(node = cn.Begin(); node != cn.End(); node++){
            printf("node\n");
            for(node2 = cn.Begin(); node2 != cn.End(); node2++){
                double weight = 0;
                for(node3 = cn.Begin(); node3 != cn.End(); node3++){
                    double* p1 = cn.getEdge(node.getNodeId(), node3.getNodeId());
                    double* p2 = cn.getEdge(node3.getNodeId(), node2.getNodeId());
                    if(p1 && p2)
                        weight += *p1 * *p2;
                }
                double *e = res.getEdge(node.getNodeId(), node2.getNodeId());
                if(e)
                    *e = weight;
                else
                    res.addEdge(node.getNodeId(), node2.getNodeId(), weight);
            }
        }
    return res;
}

CachedComplexNetwork<int, double> RandomWalk::convertToWalkNetwork(FeaturesComplexNetwork featureNetwork){
    CachedComplexNetwork<int, double> cn(true);

    FeaturesComplexNetwork::NodeIterator nodes;
    FeaturesComplexNetwork::EdgeIterator edges;
    for( nodes = featureNetwork.Begin(); nodes != featureNetwork.End(); nodes++){
         cn.addNode(nodes.getNodeId());
    }
    for( nodes = featureNetwork.Begin(); nodes != featureNetwork.End(); nodes++){
        for( edges = featureNetwork.EdgesBegin(nodes.getNodeId()); edges != featureNetwork.EdgesEnd(nodes.getNodeId()); edges++ ){
            cn.addEdge( cn.getNodeId(nodes.getNodeId()), cn.getNodeId(edges.getToNodeId()), edges->getWeight() );
        }
    }

    return cn;
}

CachedComplexNetwork<int, double> RandomWalk::normalizeGraph(CachedComplexNetwork<int, double> complexNetwork){
    CachedComplexNetwork<int, double> cn = complexNetwork;
    CachedComplexNetwork<int, double>::NodeIterator nodes;
    CachedComplexNetwork<int, double>::EdgeIterator edges;
    for( nodes = cn.Begin(); nodes != cn.End(); nodes++){
        //sum weights
        double weight = 0.0;
        for( edges = nodes.EdgesBegin(); edges != nodes.EdgesEnd(); edges++ ){
                weight += *edges;
        }
        for( edges = nodes.EdgesBegin(); edges != nodes.EdgesEnd(); edges++ ){
                *edges = *edges/weight;
        }
    }
    return cn;
}

CachedComplexNetwork<int, double> RandomWalk::addAutoLoop(CachedComplexNetwork<int, double> cn){
    for(auto n = cn.Begin(); n != cn.End(); n++){
        if(cn.getEdge(n.getNodeId(), n.getNodeId()) == NULL){
            cn.addEdge(n.getNodeId(), n.getNodeId(), 1);
        }
    }
    return cn;
}
