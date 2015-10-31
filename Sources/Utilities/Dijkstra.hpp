//
// Created by Guilherme Wachs on 30/10/15.
//

#ifndef PHDTHESIS_DIJKSTRA_HPP
#define PHDTHESIS_DIJKSTRA_HPP

#include <float.h>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include "fiboqueue.h"

#define INFINITE FLT_MAX

class Dijkstra {
private:
    const FeaturesComplexNetwork &cn;
    typedef FeaturesComplexNetwork::NodeIt NodeIt;
    typedef FeaturesComplexNetwork::Node Node;
    typedef FeaturesComplexNetwork::OutArcIt OutArcIt;
    FibQueue<float> dists;
    QHash<Node,FibQueue<float>::FibNode*> ind;
    QHash<FibQueue<float>::FibNode*,Node> revInd;
    void relax(const Node &a, const Node &b, float weight);

public:
    Dijkstra(const FeaturesComplexNetwork &cn);
    void reset();
    FeaturesComplexNetwork::NodeMap<float> run(const Node& from);

};


#endif //PHDTHESIS_DIJKSTRA_HPP
