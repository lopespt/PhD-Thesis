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
            double ecc=0;
            FeaturesComplexNetwork::NodeMap<double> dijDist(cn);
            dijkstra(cn, lenghts).distMap(dijDist).run(node);
            /*Dijkstra<FeaturesComplexNetwork, FeaturesComplexNetwork::ArcMap<double>> dij(cn, lenghts);
            dij.init();
            dij.addSource(node);
            dij.start();*/
            dist->mut.lock();
            for (FeaturesComplexNetwork::NodeIt d(cn); d != INVALID; ++d) {
                auto distancia = dijDist[d];
                if (distancia != INFINITE && distancia > ecc){
                    ecc = distancia;
                }

                //fprintf(dist->outfile, "%-5d\t%-5d\t%-20.4f\n", cn.id(node), cn.id(d), dijDist[d]);
                //dist->dist.append({node, d, dijDist[d]});
            }

            if(ecc > this->dist->diameter){
                this->dist->diameter = ecc;
                this->dist->mostDistantFrom = node;
                this->dist->mostDistantTo = node;
            }

            if(ecc < this->dist->radius){
                this->dist->radius = ecc;
            }

            if(ecc>0 && ecc < this->dist->radiusExpZero){
                this->dist->radiusExpZero = ecc;
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

