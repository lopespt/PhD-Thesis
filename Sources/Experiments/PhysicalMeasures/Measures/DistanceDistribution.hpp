//
// Created by Guilherme Wachs on 25/10/15.
//

#ifndef PHDTHESIS_DISTANCEDISTRIBUTION_HPP
#define PHDTHESIS_DISTANCEDISTRIBUTION_HPP


#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <qmap.h>
#include <lemon/core.h>

class DistanceDistribution {
public:
    typedef FeaturesComplexNetwork::Node Node;
    typedef QPair<Node,Node> Key;
    QHash<Key, float> dist;

    //lemon::ListDigraph graph;

private:
    const FeaturesComplexNetwork &cn;
    int maxThreads;

public:
    DistanceDistribution(const FeaturesComplexNetwork &cn, int maxThreads=30);
    void run();
    QHash<DistanceDistribution::Key, float> getDistances() const;

};


#endif //PHDTHESIS_DISTANCEDISTRIBUTION_HPP
