//
// Created by Guilherme Wachs on 25/10/15.
//

#include <float.h>
#include <lemon/dijkstra.h>
#include <assert.h>
#include "DistanceTask.hpp"


DistanceTask::DistanceTask(DistanceDistribution* dist, const FeaturesComplexNetwork &cn, const FeaturesComplexNetwork::ArcMap<double> &lenghts, const QList<FeaturesComplexNetwork::Node> nodes): dist(dist) ,cn(cn), lenghts(lenghts), nodes(nodes) {
    setAutoDelete(true);
}

void DistanceTask::run() {
    int n=0;
    for(auto &node: nodes) {
        try {
            FeaturesComplexNetwork::NodeMap<double> dijDist(cn);
            dijkstra(cn, lenghts).distMap(dijDist).run(node);
            /*Dijkstra<FeaturesComplexNetwork, FeaturesComplexNetwork::ArcMap<double>> dij(cn, lenghts);
            dij.init();
            dij.addSource(node);
            dij.start();*/
            dist->mut.lock();
            for (FeaturesComplexNetwork::NodeIt d(cn); d != INVALID; ++d) {
                if (dijDist[d] != INFINITE)
                    dist->dist[{node, d}] = dijDist[d];
            }
        }catch (exception e) {
            puts("excessao");
        }
        if( n % 20 == 0 ) {
            dist->te.print();
            fflush(stdout);
        }
        n++;
        dist->te.tick();
        dist->mut.unlock();
    }
    dist->mut.lock();
    dist->te.print();
    dist->mut.unlock();
}

