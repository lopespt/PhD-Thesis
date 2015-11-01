//
// Created by Guilherme Wachs on 25/10/15.
//

#include <float.h>
#include <lemon/dijkstra.h>
#include <assert.h>
#include "DistanceTask.hpp"


DistanceTask::DistanceTask(DistanceDistribution* dist, const FeaturesComplexNetwork &cn, const FeaturesComplexNetwork::ArcMap<double> &dists, const QList<FeaturesComplexNetwork::Node> nodes): dist(dist) ,cn(cn), dists(dists), nodes(nodes) {
    setAutoDelete(true);
}

void DistanceTask::run() {
    int n=0;
    for(auto &node: nodes) {
        FeaturesComplexNetwork::NodeMap<double> dijDist(cn);
        dijkstra(cn, dists).distMap(dijDist).run(node);
        dist->mut.lock();
        puts("Terminei Dijkstra... Setando Nos");
        for(FeaturesComplexNetwork::NodeIt d(cn); d != INVALID; ++d){
            if(dijDist[d]!=INFINITE)
                dist->dist[{node,d}]=dijDist[d];
        }
        puts("Terminei Setar Nos");
        if( n % 20 == 0 )
            dist->te.print();
        n++;
        dist->te.tick();
        dist->mut.unlock();
    }
    dist->mut.lock();
    dist->te.print();
    dist->mut.unlock();
}

