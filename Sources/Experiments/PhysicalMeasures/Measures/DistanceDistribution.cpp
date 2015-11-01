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


DistanceDistribution::DistanceDistribution(const FeaturesComplexNetwork &cn, int maxThreads) : te(cn.getNumNodes()), cn(cn), maxThreads(maxThreads) {
}

void DistanceDistribution::run() {
    QThreadPool pool;
    pool.setMaxThreadCount(maxThreads);
    FILE *fo = fopen("time.txt","w");

    FeaturesComplexNetwork::ArcMap<double> dists(cn);
    getDistMap(dists);
    Dijkstra<FeaturesComplexNetwork, FeaturesComplexNetwork::ArcMap<double>> dij(cn,dists);

    QVector<QList<Node> > threadsNodes(maxThreads);
    threadsNodes.append(QList<Node>());
    int threadNum=0;
    for(FeaturesComplexNetwork::NodeIt k(cn); k != INVALID; ++k) {
        threadsNodes[threadNum].append(k);
        threadNum++;
        if(threadNum % maxThreads == 0) {
            threadNum=0;
        }
    }
    for(auto &threadNodesItem : threadsNodes ){
        pool.start(new DistanceTask(this,cn,dists, threadNodesItem));

        /*dij.run(k);
        for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it) {
            dist[{k,it}]=dij.dist(it);
        }
           */
    }
    /*pool.waitForDone();
    for(auto &t : threads){
        this->dist.unite(t->getDists());
        delete t;
    }
    threads.clear();
*/
    fclose(fo);
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

DistanceDistribution::~DistanceDistribution() {
    /*for(auto &t: threads){
        delete t;
    }*/
    threads.clear();
}


const QHash<DistanceDistribution::Key, double> DistanceDistribution::getDist() const {
    return this->dist;
}
