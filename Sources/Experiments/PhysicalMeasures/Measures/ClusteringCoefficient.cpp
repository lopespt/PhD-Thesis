//
// Created by Guilherme Wachs on 21/10/15.
//

#include <random>
#include <Utilities/Utils.hpp>
#include <Utilities/GraphUtilities.hpp>
#include <qthreadpool.h>
#include "ClusteringCoefficient.hpp"
#include "ClusteringCoefficientTask.hpp"

ClusteringCoefficient::ClusteringCoefficient(FeaturesComplexNetwork &cn, int threads, float ratio) : cn(cn), threads(threads), ratio(ratio), te(cn.getNumNodes()) {
}

float ClusteringCoefficient::Compute() {
    QList<FeaturesComplexNetwork::Node> ids;
    ids.reserve(cn.getNumNodes());
    for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it){
        ids.append( it );
    }
    std::random_shuffle(ids.begin(), ids.end());

    QList<QList<FeaturesComplexNetwork::Node>> lists;
    lists.append(QList<FeaturesComplexNetwork::Node>());

    int j=0;
    for(int i=0;i< ids.size()*ratio; i++){
        lists.last().append(ids[i]);
        j++;
        if( j > 50 ){
            j=0;
            lists.append(QList<FeaturesComplexNetwork::Node>());
        }
    }


    FeaturesComplexNetwork::ArcMap<double> weights(cn);
    GraphUtilities::getWeights(cn, weights);
    GraphUtilities::normalizeWeights(cn,weights,weights);

    QThreadPool pool;
    pool.setMaxThreadCount(this->threads);
    for(auto &list : lists) {
        pool.start(new ClusteringCoefficientTask(this, cn, weights, list));
    }
    pool.waitForDone();

    return std::accumulate(ccs.begin(),ccs.end(),0.f, [](const float &a, const ClusteringCoefficient::NodeCC &b){return a+b.cc;})/ccs.size();
}

