//
// Created by Guilherme Wachs on 25/10/15.
//

#ifndef PHDTHESIS_DISTANCETASK_HPP
#define PHDTHESIS_DISTANCETASK_HPP


#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <qthread.h>
#include <qrunnable.h>
#include <float.h>
#include <lemon/dijkstra.h>
#include "DistanceDistribution.hpp"

#define INFINITE FLT_MAX

class DistanceDistribution;
class DistanceTask : public QRunnable {
private:
    DistanceDistribution *dist;
    const FeaturesComplexNetwork &cn;
    const FeaturesComplexNetwork::ArcMap<double> &lenghts;
    const QList<FeaturesComplexNetwork::Node> nodes;

    typedef FeaturesComplexNetwork::Node Node;
    typedef QPair<Node,Node> Key;

public:
    DistanceTask(DistanceDistribution *dist,const FeaturesComplexNetwork& cn, const FeaturesComplexNetwork::ArcMap<double> &lenghts, const QList<FeaturesComplexNetwork::Node> nodes );
    virtual void run() override;
};


#endif //PHDTHESIS_DISTANCETASK_HPP
