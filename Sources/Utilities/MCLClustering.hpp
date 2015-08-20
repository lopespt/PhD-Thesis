//
// Created by Guilherme Wachs on 13/08/15.
//

#ifndef PHDTHESIS_MCLCLUSTERING_HPP
#define PHDTHESIS_MCLCLUSTERING_HPP

#include <lemon/list_graph.h>
#include "GraphUtilities.hpp"
#include <QList>
#include <QSet>

using namespace lemon;

class MCLClustering {
private:
    FeaturesComplexNetwork &cn;
    ListDigraph::ArcMap<double> weights;
    ListDigraph::NodeMap<float> outDeg;
    ListDigraph::NodeMap<int> clusterNum;
    QList<QList<FeaturesComplexNetwork::Node>> clusters;

public:
    MCLClustering(FeaturesComplexNetwork &cn, const ListDigraph::ArcMap <double> &weights): cn(cn), weights(cn), outDeg(cn), clusterNum(cn) {
        GraphUtilities::normalizeOutDegrees(this->cn, weights, this->weights);
        GraphUtilities::addAutoLoop(this->cn, this->weights);
        GraphUtilities::normalizeOutDegrees(this->cn, this->weights, this->weights);
        //GraphUtilities::copyMap(this->cn, weights, this->weights);
    }
    float execute();
    int getClusterNum(FeaturesComplexNetwork::Node n);
    QList<FeaturesComplexNetwork::Node> getClusterNodes(int clusterNum);
    int getTotalClusters();
    const FeaturesComplexNetwork::NodeMap<int> & getClustersMap();


};


#endif //PHDTHESIS_MCLCLUSTERING_HPP
