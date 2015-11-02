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


DistanceDistribution::DistanceDistribution(FeaturesComplexNetwork &cn, int maxThreads, const char* outputFile) : te(cn.getNumNodes()), cn(cn), maxThreads(maxThreads) {
    this->outfile = fopen(outputFile,"w");
    this->diameter = 0;
    this->radius = INFINITE;
    this->radiusExpZero = INFINITE;
}

void DistanceDistribution::run() {
    QThreadPool pool;
    pool.setMaxThreadCount(maxThreads);

    FeaturesComplexNetwork::ArcMap<double> lenghts(cn);
    getDistMap(lenghts);
    //Dijkstra<FeaturesComplexNetwork, FeaturesComplexNetwork::ArcMap<double>> dij(cn,lenghts);

    QVector<QList<Node> > threadsNodes;
    threadsNodes.append(QList<Node>());
    int numNodes=0;
    puts("Criando lista de nos");

    for(FeaturesComplexNetwork::NodeIt k(cn); k != INVALID; ++k) {
        threadsNodes.last().append(k);
        numNodes++;
        if(numNodes >= 100) {
            numNodes=0;
            threadsNodes.append(QList<Node>());
        }
    }
    puts("Termino lista de nos");
    puts("Iniciando Threads");
    for(auto &threadNodesItem : threadsNodes ){
        pool.start(new DistanceTask(this,cn,lenghts, threadNodesItem));

        /*dij.run(k);
        for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it) {
            dist[{k,it}]=dij.dist(it);
        }
           */
    }
    pool.waitForDone();
    puts("=====Resultado FINAL===========");
    printf("radiusExpZero: %f\n", radiusExpZero );
    printf("radius: %f\n", radius );
    printf("diameter: %f\n", diameter);
    fflush(stdout);
    printf("diameter: %d %d %f\n", cn.id(mostDistantFrom), cn.id(mostDistantTo), diameter);
    /*
    for(auto &t : threads){
        this->dist.unite(t->getDists());
        delete t;
    }
    threads.clear();
*/
}


void DistanceDistribution::getDistMap(FeaturesComplexNetwork::ArcMap<double> &dmap) {
    GraphUtilities::getWeights(cn, dmap);
    for(FeaturesComplexNetwork::ArcIt it(cn); it != INVALID; ++it){
        if( cn.getLinkArcValue(it).type == Link::LinkType::OtherLabel ){
            //dmap[it] = 1.0/cn.getLinkArcValue(it).getWeight();
            dmap[it] = 1.0;
        }else{
            cn.erase(it);
            //dmap[it] = INFINITE;
        }
    }

}

DistanceDistribution::~DistanceDistribution() {
    /*for(auto &t: threads){
        delete t;
    }*/
    threads.clear();
    fclose(this->outfile);
}


