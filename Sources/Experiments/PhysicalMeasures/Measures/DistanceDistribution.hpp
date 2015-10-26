//
// Created by Guilherme Wachs on 25/10/15.
//

#ifndef PHDTHESIS_DISTANCEDISTRIBUTION_HPP
#define PHDTHESIS_DISTANCEDISTRIBUTION_HPP


#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <qmap.h>
#define INFINITE FLT_MAX

class DistanceDistribution {
public:
    typedef FeaturesComplexNetwork::Node Node;
    typedef QPair<Node,Node> Key;
    QHash<Key, float> dist;
private:
    const FeaturesComplexNetwork &cn;

public:
    DistanceDistribution(const FeaturesComplexNetwork &cn);
    void run();

};


#endif //PHDTHESIS_DISTANCEDISTRIBUTION_HPP
