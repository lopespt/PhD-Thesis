#ifndef ITERATIVERANDOMWALK_HPP
#define ITERATIVERANDOMWALK_HPP

#include <stdlib.h>
#include <QVector>
#include <set>
#include <lemon/list_graph.h>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>

using namespace std;

using namespace lemon;
class IterativeRandomWalk {
public:
    typedef FeaturesComplexNetwork::NodeMap<double> NodeMapDouble;
    typedef FeaturesComplexNetwork::ArcMap<double> ArcMapDouble;
private:
    const FeaturesComplexNetwork &cn;
    FeaturesComplexNetwork::ArcMap <double> weights;
    FeaturesComplexNetwork::NodeMap <double> probs;
    FeaturesComplexNetwork::NodeMap <double> probs2;

    void clearMap(NodeMapDouble &map);
    void clearMap(FeaturesComplexNetwork::ArcMap<double> &map);

public:


    IterativeRandomWalk(const FeaturesComplexNetwork &cn);
    IterativeRandomWalk(const FeaturesComplexNetwork &cn, const FeaturesComplexNetwork::ArcMap <double> &weights);

    void setWeights(ArcMapDouble &map);

    void Execute(FeaturesComplexNetwork::Node start_node, unsigned int max_path_length);

    double getProbability(ListDigraph::Node node);

    void getAllProbs(NodeMapDouble &map);
};

#endif // ITERATIVERANDOMWALK_HPP
