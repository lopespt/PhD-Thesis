//
// Created by Guilherme Wachs on 21/10/15.
//

#ifndef PHDTHESIS_CLUSTERINGCOEFFICIENT_HPP
#define PHDTHESIS_CLUSTERINGCOEFFICIENT_HPP


#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>

#include <QList>
#include <Utilities/TimeEstimator.hpp>
#include <QMutex>

class ClusteringCoefficient {
private:
    FeaturesComplexNetwork &cn;
    int threads;
    float ratio;
public:
    typedef struct {
        FeaturesComplexNetwork::Node id;
        float cc;
    }NodeCC;
    QList<NodeCC> ccs;
    QMutex mut;
    TimeEstimator te;
    ClusteringCoefficient (FeaturesComplexNetwork &cn, int threads, float ratio);

    float Compute();
};


#endif //PHDTHESIS_CLUSTERINGCOEFFICIENT_HPP
