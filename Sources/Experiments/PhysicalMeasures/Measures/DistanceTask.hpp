//
// Created by Guilherme Wachs on 25/10/15.
//

#ifndef PHDTHESIS_DISTANCETASK_HPP
#define PHDTHESIS_DISTANCETASK_HPP


#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <qthread.h>
#include <qrunnable.h>
#include "DistanceDistribution.hpp"

class DistanceTask : public QRunnable {
private:
    typedef DistanceDistribution::Key Key;
    const FeaturesComplexNetwork &cn;
    QHash<DistanceDistribution::Key, float>& dist ;
    const FeaturesComplexNetwork::NodeIt &it;
public:
    DistanceTask(const FeaturesComplexNetwork& cn, QHash<DistanceDistribution::Key, float>& dist ,const FeaturesComplexNetwork::NodeIt &it);
    virtual void run() override;
};


#endif //PHDTHESIS_DISTANCETASK_HPP
