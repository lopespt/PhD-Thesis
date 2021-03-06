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
    puts("Iniciando Thread");
    for(auto &node: nodes) {
            double ecc=0;
            Node dest;
            FeaturesComplexNetwork::NodeMap<double> dijDist(cn);
            dijkstra(cn, lenghts).distMap(dijDist).run(node);
            /*Dijkstra<FeaturesComplexNetwork, FeaturesComplexNetwork::ArcMap<double>> dij(cn, lenghts);
            dij.init();
            dij.addSource(node);
            dij.start();*/
            for (FeaturesComplexNetwork::NodeIt d(cn); d != INVALID; ++d) {
                auto distancia = dijDist[d];
                if (distancia != INFINITE && distancia > ecc){
                    ecc = distancia;
                    dest = d;
                }

                //fprintf(dist->outfile, "%-5d\t%-5d\t%-20.4f\n", cn.id(node), cn.id(d), dijDist[d]);
                //dist->dist.append({node, d, dijDist[d]});
            }
            dist->mut.lock();
            fprintf(dist->outfile, "%d\t%d\t%-20.5f\n", cn.id(node), cn.id(dest), ecc);

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
    printf("radiusExpZero: %f\n", dist->radiusExpZero );
    printf("radius: %f\n", dist->radius );
    printf("diameter: %f\n", dist->diameter);
    printf("diameter: %d %d %f\n", cn.id(dist->mostDistantFrom), cn.id(dist->mostDistantTo), dist->diameter);
    fflush(stdout);
    dist->mut.unlock();
}

