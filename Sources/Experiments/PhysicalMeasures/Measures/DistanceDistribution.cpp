//
// Created by Guilherme Wachs on 25/10/15.
//

#include <float.h>
#include <qthreadpool.h>
#include <Utilities/TimeEstimator.hpp>
#include "DistanceDistribution.hpp"
#include "DistanceTask.hpp"


DistanceDistribution::DistanceDistribution(const FeaturesComplexNetwork &cn) : cn(cn) {

    for(FeaturesComplexNetwork::NodeIt i(cn); i != INVALID; ++i) {
        for (FeaturesComplexNetwork::NodeIt j(cn); j != INVALID; ++j) {
            if(cn.arcExists(i,j,Link::LinkType::OtherLabel)) {
                dist[Key(i, j)] = 1.0/cn.getLinkArcValue(i,j,Link::LinkType::OtherLabel).getWeight();
            }else{
                dist[Key(i, j)] = INFINITE;
            }
        }
    }
}

void DistanceDistribution::run() {
    int n=0;
    int m=cn.getNumNodes();
    QThreadPool pool;
    pool.setMaxThreadCount(30);
    TimeEstimator te(cn.getNumNodes());
    FILE *fo = fopen("time.txt","w");
    for(FeaturesComplexNetwork::NodeIt k(cn); k != INVALID; ++k){
        te.tick();
        n++;
        printf("%-5d | %-5d (%.0f)\n", n,m, n*1./m*100. );
        pool.start(new DistanceTask(cn,dist,k));
        if(n%30==0){
            fprintf(fo, "%d\t%ld\n",te.getTicks() , te.getElapsedTime());
            fflush(fo);
            te.print();
            pool.waitForDone();
        }
/*        for(FeaturesComplexNetwork::NodeIt i(cn); i != INVALID; ++i) {
            for (FeaturesComplexNetwork::NodeIt j(cn); j != INVALID; ++j) {
                dist[Key(i,j)] = std::min(dist[Key(i,j)], dist[Key(i,k)] + dist[Key(k,j)]);
            }
        }
    */
    }
    pool.waitForDone();
}

QHash<DistanceDistribution::Key, float> DistanceDistribution::getDistances() const {
    return this->dist;
}
