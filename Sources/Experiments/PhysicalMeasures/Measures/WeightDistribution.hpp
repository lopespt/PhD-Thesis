//
// Created by Guilherme Wachs on 25/10/15.
//

#ifndef PHDTHESIS_WEIGHTDISTRIBUTION_HPP
#define PHDTHESIS_WEIGHTDISTRIBUTION_HPP


#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <qmap.h>

class WeightDistribution {
public:
    typedef QMap<FeaturesComplexNetwork::Arc, float>  ArcMap;
private:
    const FeaturesComplexNetwork& cn;
    ArcMap weights;
    bool contextOnly=true;
public:


    WeightDistribution(const FeaturesComplexNetwork &cn);

    ArcMap getWeightsDistribution() const;
    void run();

};


#endif //PHDTHESIS_WEIGHTDISTRIBUTION_HPP
