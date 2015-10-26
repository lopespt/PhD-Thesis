//
// Created by Guilherme Wachs on 21/10/15.
//

#ifndef PHDTHESIS_CLUSTERINGCOEFFICIENT_HPP
#define PHDTHESIS_CLUSTERINGCOEFFICIENT_HPP


#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include "ClusteringCoefficientTask.hpp"

#include <QList>
class ClusteringCoefficient {
public:
    static float Compute(FeaturesComplexNetwork &cn, int threads, float ratio);
};


#endif //PHDTHESIS_CLUSTERINGCOEFFICIENT_HPP
