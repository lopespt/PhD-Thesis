//
// Created by Guilherme Wachs on 21/10/15.
//

#include <random>
#include <Utilities/Utils.hpp>
#include <Utilities/GraphUtilities.hpp>
#include <qthreadpool.h>
#include "ClusteringCoefficient.hpp"
#include "ClusteringCoefficientTask.hpp"

float ClusteringCoefficient::Compute(FeaturesComplexNetwork &cn, int threads, float ratio) {
    QList<FeaturesComplexNetwork::Node> ids;
    ids.reserve(cn.getNumNodes());
    for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it){
        ids.append( it );
    }
    std::random_shuffle(ids.begin(), ids.end());

    QList<QList<FeaturesComplexNetwork::Node>> lists;
    for(int i=0;i<threads;i++){
        lists.append(QList<FeaturesComplexNetwork::Node>());
    }

    int j=0;
    for(int i=0;i< ids.size()*ratio; i++){
        lists[j].append(ids[i]);
        j = (j + 1) % threads;
    }


    FeaturesComplexNetwork::ArcMap<double> weights(cn);
    GraphUtilities::getWeights(cn, weights);
    GraphUtilities::normalizeWeights(cn,weights,weights);

    QList<ClusteringCoefficientTask*> tasks;
    for(int i=0;i<threads;i++) {
        tasks.append(new ClusteringCoefficientTask(cn,weights,lists[i]));
        tasks[i]->start();
    }

    QList<ClusteringCoefficientTask::NodeCC> ccs;
    for(int i=0;i<threads;i++) {
        tasks[i]->wait();
        ccs.append(tasks[i]->getResults());
    }

    for(int i=0;i<threads;i++)
        delete tasks[i];

    return std::accumulate(ccs.begin(),ccs.end(),0.f, [](const float &a, const ClusteringCoefficientTask::NodeCC &b){return a+b.cc;})/ccs.size();
}
