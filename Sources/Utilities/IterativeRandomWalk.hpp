#ifndef ITERATIVERANDOMWALK_HPP
#define ITERATIVERANDOMWALK_HPP

#include <stdlib.h>
#include <QVector>
#include <set>
#include <lemon/list_graph.h>

using namespace std;

using namespace lemon;
class IterativeRandomWalk {
public:
    typedef ListDigraph::NodeMap<double> NodeMapDouble;
    typedef ListDigraph::ArcMap<double> ArcMapDouble;
private:
    ListDigraph &cn;
    ListDigraph::ArcMap <double> weights;
    ListDigraph::NodeMap <double> probs;
    ListDigraph::NodeMap <double> probs2;

    void clearMap(NodeMapDouble &map);
    void clearMap(ListDigraph::ArcMap<double> &map);

public:


    IterativeRandomWalk(ListDigraph &cn);
    IterativeRandomWalk(ListDigraph &cn, const ListDigraph::ArcMap <double> &weights);

    void setWeights(ArcMapDouble &map);

    void Execute(ListDigraph::Node start_node, unsigned int max_path_length);

    double getProbability(ListDigraph::Node node);

    void getAllProbs(NodeMapDouble &map);
};

#endif // ITERATIVERANDOMWALK_HPP
