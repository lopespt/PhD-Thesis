//
// Created by Guilherme Wachs on 25/10/15.
//

#include <float.h>
#include <lemon/dijkstra.h>
#include "DistanceTask.hpp"


DistanceTask::DistanceTask(const FeaturesComplexNetwork &cn, const FeaturesComplexNetwork::ArcMap<double> &dists, const QList<FeaturesComplexNetwork::Node> nodes):cn(cn), dij(cn,dists), nodes(nodes) {
    setAutoDelete(true);
}

void DistanceTask::run() {
    for(auto &node: nodes) {
        dij.run(node);
        for(FeaturesComplexNetwork::NodeIt d(cn); d != INVALID; ++d){
            if(dij.dist(d)!=INFINITE)
                dist[{node,d}]=dij.dist(d);
        }
    }
}
