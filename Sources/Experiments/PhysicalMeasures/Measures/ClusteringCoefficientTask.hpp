//
// Created by Guilherme Wachs on 21/10/15.
//

#ifndef PHDTHESIS_CLUSTERINGCOEFFICIENTTASK_HPP
#define PHDTHESIS_CLUSTERINGCOEFFICIENTTASK_HPP

#include <QRunnable>
#include <QList>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include "ClusteringCoefficient.hpp"

class ClusteringCoefficientTask : public QRunnable {
public:

private:
    typedef ClusteringCoefficient::NodeCC NodeCC;
    ClusteringCoefficient *parent;
    const FeaturesComplexNetwork &cn;
    const FeaturesComplexNetwork::ArcMap<double>& weights;
    QList<FeaturesComplexNetwork::Node> nodes;

    float computeCC(FeaturesComplexNetwork::Node) const;

public:

    ClusteringCoefficientTask(ClusteringCoefficient* parent, const FeaturesComplexNetwork& cn, const FeaturesComplexNetwork::ArcMap<double>& weights, QList<FeaturesComplexNetwork::Node> nodes);



protected:
    virtual void run() override;
};


#endif //PHDTHESIS_CLUSTERINGCOEFFICIENTTASK_HPP
