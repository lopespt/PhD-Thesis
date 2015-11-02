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
    TimeEstimator te;
    QVector<DistanceTask*> threads;
    QMutex mut;
    FILE* outfile;
    double diameter;
    double radius;
    double radiusExpZero;
    Node mostDistantFrom;
    Node mostDistantTo;
private:
    FeaturesComplexNetwork &cn;
    int maxThreads;
    void getDistMap(FeaturesComplexNetwork::ArcMap<double> &dmap);
public:
    DistanceDistribution(FeaturesComplexNetwork &cn, int maxThreads=30, const char* outputFile="distancias.txt");
    void run();
    ~DistanceDistribution();

};


#endif //PHDTHESIS_DISTANCEDISTRIBUTION_HPP
