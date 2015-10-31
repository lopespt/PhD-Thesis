//
// Created by Guilherme Wachs on 25/10/15.
//

#include <qthreadpool.h>
#include <Utilities/TimeEstimator.hpp>
#include <lemon/dijkstra.h>
#include <Utilities/GraphUtilities.hpp>
#include <qvector.h>
//#include <Utilities/Dijkstra.hpp>
#include "DistanceDistribution.hpp"
#include "DistanceTask.hpp"


DistanceDistribution::DistanceDistribution(const FeaturesComplexNetwork &cn, int maxThreads) : cn(cn), maxThreads(maxThreads) {

}

void DistanceDistribution::run() {
    int n=0;
    QThreadPool pool;
    pool.setMaxThreadCount(maxThreads);
    TimeEstimator te(cn.getNumNodes());
    FILE *fo = fopen("time.txt","w");

    FeaturesComplexNetwork::ArcMap<double> dists(cn);
    getDistMap(dists);

    QVector<QList<Node> > threadsNodes;
    threadsNodes.append(QList<Node>());
    for(FeaturesComplexNetwork::NodeIt k(cn); k != INVALID; ++k){
        threadsNodes.last().append(k);

        if(threadsNodes.last().size() >= 20){
            pool.start(new DistanceTask(cn,dists, threadsNodes.last()));
            threadsNodes.push_back(QList<Node>());
        }
        if(pool.activeThreadCount() >= maxThreads){
            pool.waitForDone();
        }
        te.tick();
        te.print();
    }
    pool.waitForDone();
    fclose(fo);
}

QHash<DistanceDistribution::Key, double> DistanceDistribution::getDistances() const {
    return this->dist;
}

void DistanceDistribution::getDistMap(FeaturesComplexNetwork::ArcMap<double> &dmap) {
    GraphUtilities::getWeights(cn, dmap);
    for(FeaturesComplexNetwork::ArcIt it(cn); it != INVALID; ++it){
        if( cn.getLinkArcValue(it).type == Link::LinkType::OtherLabel ){
            dmap[it] = 1.0/cn.getLinkArcValue(it).getWeight();
        }else{
            dmap[it] = INFINITE;
        }
    }

}
