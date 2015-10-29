//
// Created by Guilherme Wachs on 25/10/15.
//

#include <qthreadpool.h>
#include <Utilities/TimeEstimator.hpp>
#include <sqltypes.h>
#include "DistanceDistribution.hpp"
#include "DistanceTask.hpp"


DistanceDistribution::DistanceDistribution(const FeaturesComplexNetwork &cn, int maxThreads) : cn(cn), maxThreads(maxThreads) {

    TimeEstimator tt(cn.getNumArcs());
    int n=0;
    //for(FeaturesComplexNetwork::NodeIt i(cn); i != INVALID; ++i) {
      //  for (FeaturesComplexNetwork::NodeIt j(cn); j != INVALID; ++j) {
    for(FeaturesComplexNetwork::ArcIt arc(cn); arc != INVALID; ++arc ){
            n++;
            Node n1=cn.source(arc);
            Node n2=cn.target(arc);
            if(cn.arcExists( n1, n2 ,Link::LinkType::OtherLabel)) {
                dist[Key(n1,n2)] = (float) (1.0 / cn.getLinkArcValue(n1, n2, Link::LinkType::OtherLabel).getWeight());
            }
        //}
        tt.tick();
        if(n%100 == 0)
            tt.print();
    }
}

void DistanceDistribution::run() {
    int n=0;
    int m=cn.getNumNodes();
    QThreadPool pool;
    pool.setMaxThreadCount(maxThreads);
    TimeEstimator te(cn.getNumNodes());
    FILE *fo = fopen("time.txt","w");
    for(FeaturesComplexNetwork::NodeIt k(cn); k != INVALID; ++k){
        te.tick();
        n++;
        printf("%-5d | %-5d (%.0f)\n", n,m, n*1./m*100. );
        pool.start(new DistanceTask(cn,dist,k));
        if(n%maxThreads==0){
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
    fclose(fo);
}

QHash<DistanceDistribution::Key, float> DistanceDistribution::getDistances() const {
    return this->dist;
}
