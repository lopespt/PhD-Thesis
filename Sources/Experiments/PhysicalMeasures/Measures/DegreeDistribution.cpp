//
// Created by Guilherme Wachs on 25/10/15.
//

#include <Utilities/TimeEstimator.hpp>
#include "DegreeDistribution.hpp"
DegreeDistribution::DegreeDistribution(const FeaturesComplexNetwork &cn) : cn(cn) {
    for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it ){
        outDegrees[it] = 0;
        inDegrees[it] = 0;
        SumOutDegrees[it] = 0;
        SumInDegrees[it] = 0;
    }
}

const DegreeDistribution::NodeMap DegreeDistribution::getOutDegrees() const {
    return this->outDegrees;
}

const DegreeDistribution::NodeMap DegreeDistribution::getInDegrees() const {
    return this->inDegrees;
}

const DegreeDistribution::NodeMap DegreeDistribution::getSumOutDegrees() const {
    return this->SumOutDegrees;
}

const DegreeDistribution::NodeMap DegreeDistribution::getSumInDegrees() const {
    return this->SumInDegrees;
}

void DegreeDistribution::run() {
    TimeEstimator te(cn.getNumArcs());
    int i=0;
    for(FeaturesComplexNetwork::ArcIt it(cn); it != INVALID; ++it ){
        te.tick();
        if(!onlyContexts || cn.getLinkArcValue(it).getLinkType()==Link::LinkType::OtherLabel ) {
            outDegrees[cn.source(it)]++;
            inDegrees[cn.target(it)]++;
            SumOutDegrees[cn.source(it)] += cn.getLinkArcValue(it).getWeight();
            SumInDegrees[ cn.target(it)] += cn.getLinkArcValue(it).getWeight();
        }
        i++;
        if(i % 1000 == 0)
            te.print();
    }
}

