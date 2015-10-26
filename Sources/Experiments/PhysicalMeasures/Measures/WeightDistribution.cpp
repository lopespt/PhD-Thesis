//
// Created by Guilherme Wachs on 25/10/15.
//

#include "WeightDistribution.hpp"
WeightDistribution::WeightDistribution(const FeaturesComplexNetwork &cn) : cn(cn) {

}

WeightDistribution::ArcMap WeightDistribution::getWeightsDistribution() const {
    return this->weights;
}

void WeightDistribution::run() {
    for( FeaturesComplexNetwork::ArcIt it(cn); it != INVALID; ++it ){
        if(!contextOnly || cn.getLinkArcValue(it).getLinkType()==Link::LinkType::OtherLabel ) {
            weights[it] = cn.getLinkArcValue(it).getWeight();
        }
    }
}
