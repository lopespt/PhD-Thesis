//
// Created by Guilherme Wachs on 25/10/15.
//

#ifndef PHDTHESIS_DISTANCEDISTRIBUTION_HPP
#define PHDTHESIS_DISTANCEDISTRIBUTION_HPP


#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <qmap.h>
#include <lemon/core.h>
#include "DistanceTask.hpp"
#include <QVector>
#include <Utilities/TimeEstimator.hpp>
#include <QMutex>

class DistanceTask;
class DistanceDistribution {
public:
    typedef FeaturesComplexNetwork::Node Node;
    typedef struct{
        Node from;
        Node to;
        double peso;
    }Distancia;
    QList<Distancia> dist;
    TimeEstimator te;
    QVector<DistanceTask*> threads;
    QMutex mut;

private:
    const FeaturesComplexNetwork &cn;
    int maxThreads;
    void getDistMap(FeaturesComplexNetwork::ArcMap<double> &dmap);
public:
    DistanceDistribution(const FeaturesComplexNetwork &cn, int maxThreads=30);
    void run();
    const QList<Distancia> getDist() const;
    ~DistanceDistribution();

};


#endif //PHDTHESIS_DISTANCEDISTRIBUTION_HPP
