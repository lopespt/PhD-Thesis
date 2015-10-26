//
// Created by Guilherme Wachs on 21/10/15.
//

#ifndef PHDTHESIS_CLUSTERINGCOEFFICIENTTASK_HPP
#define PHDTHESIS_CLUSTERINGCOEFFICIENTTASK_HPP

#include <QThread>
#include <QList>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>

class ClusteringCoefficientTask : public QThread {
public:
    typedef struct {
        FeaturesComplexNetwork::Node id;
        float cc;
    }NodeCC;

private:
    const FeaturesComplexNetwork &cn;
    QList<FeaturesComplexNetwork::Node> nodes;
    QList<NodeCC> results;
    const FeaturesComplexNetwork::ArcMap<double>& weights;

    float computeCC(FeaturesComplexNetwork::Node) const;

public:

    ClusteringCoefficientTask(const FeaturesComplexNetwork& cn, const FeaturesComplexNetwork::ArcMap<double>& weights, QList<FeaturesComplexNetwork::Node> nodes);

    QList<NodeCC> getResults() const;


protected:
    virtual void run() override;
};


#endif //PHDTHESIS_CLUSTERINGCOEFFICIENTTASK_HPP
