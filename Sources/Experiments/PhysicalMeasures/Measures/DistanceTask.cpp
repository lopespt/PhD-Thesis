//
// Created by Guilherme Wachs on 25/10/15.
//

#include <float.h>
#include "DistanceTask.hpp"

DistanceTask::DistanceTask(const FeaturesComplexNetwork &cn, QHash<DistanceDistribution::Key, float> &dist,
                           const FeaturesComplexNetwork::NodeIt &it) : cn(cn), dist(dist), it(it) {
    setAutoDelete(true);
}

void DistanceTask::run() {
    for(FeaturesComplexNetwork::NodeIt i(cn); i != INVALID; ++i) {
        for (FeaturesComplexNetwork::NodeIt j(cn); j != INVALID; ++j) {
            if(dist.contains(Key(i,it)) && dist.contains(Key(it,j))) {
                if(!dist.contains(Key(i,j)))
                    dist[Key(i,j)]=INFINITE;
                dist[Key(i, j)] = std::min(dist[Key(i, j)], dist[Key(i, it)] + dist[Key(it, j)]);
            }
        }
    }
}

