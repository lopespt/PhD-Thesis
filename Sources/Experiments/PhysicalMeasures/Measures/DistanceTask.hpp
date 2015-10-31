//
// Created by Guilherme Wachs on 25/10/15.
//

#ifndef PHDTHESIS_DISTANCETASK_HPP
#define PHDTHESIS_DISTANCETASK_HPP


#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <qthread.h>
#include <qrunnable.h>
#include "DistanceDistribution.hpp"
#include <float.h>
#define INFINITE FLT_MAX

class DistanceTask : public QRunnable {
private:
    const FeaturesComplexNetwork &cn;
    Dijkstra<FeaturesComplexNetwork, FeaturesComplexNetwork::ArcMap<double> > dij;
    const QList<FeaturesComplexNetwork::Node> nodes;

    typedef FeaturesComplexNetwork::Node Node;
    typedef QPair<Node,Node> Key;
    QHash<Key, double> dist;
public:
    DistanceTask(const FeaturesComplexNetwork& cn, const FeaturesComplexNetwork::ArcMap<double> &dists, const QList<FeaturesComplexNetwork::Node> nodes );
    virtual void run() override;
};


#endif //PHDTHESIS_DISTANCETASK_HPP
