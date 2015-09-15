//
// Created by Guilherme Wachs on 25/08/15.
//

#ifndef PHDTHESIS_CLUSTERINGCOEFFICIENT_H
#define PHDTHESIS_CLUSTERINGCOEFFICIENT_H


#include "FeaturesComplexNetwork/FeaturesComplexNetwork.hpp"

class ClusteringCoefficient {
private:
    const FeaturesComplexNetwork::ArcMap<double> &weights;
    const FeaturesComplexNetwork &cn;
public:
    ClusteringCoefficient(const FeaturesComplexNetwork &cn, const FeaturesComplexNetwork::ArcMap<double> &weights): weights(weights), cn(cn){

    }

    float compute(const FeaturesComplexNetwork::Node &node);

};


#endif //PHDTHESIS_CLUSTERINGCOEFFICIENT_H
