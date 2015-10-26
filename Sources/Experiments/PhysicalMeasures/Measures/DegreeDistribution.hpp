//
// Created by Guilherme Wachs on 25/10/15.
//

#ifndef PHDTHESIS_DEGREEDISTRIBUTION_HPP
#define PHDTHESIS_DEGREEDISTRIBUTION_HPP
#include <QSet>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <qmap.h>

class DegreeDistribution {
public:
    typedef QMap<FeaturesComplexNetwork::Node, float>  NodeMap;
private:
    const FeaturesComplexNetwork &cn;
    NodeMap outDegrees;
    NodeMap inDegrees;
    NodeMap SumInDegrees;
    NodeMap SumOutDegrees;
    bool onlyContexts=true;

public:


    DegreeDistribution(const FeaturesComplexNetwork &cn);

    const NodeMap getOutDegrees() const;
    const NodeMap getInDegrees() const;
    const NodeMap getSumOutDegrees() const;
    const NodeMap getSumInDegrees() const;

    void run();
};


#endif //PHDTHESIS_DEGREEDISTRIBUTION_HPP
