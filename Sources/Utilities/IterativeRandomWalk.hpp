#ifndef ITERATIVERANDOMWALK_HPP
#define ITERATIVERANDOMWALK_HPP

#include <stdlib.h>
#include <QVector>
#include <set>
#include <lemon/list_graph.h>

using namespace std;
using namespace lemon;

class IterativeRandomWalk {
private:
    ListDigraph &cn;
    ListDigraph::ArcMap <double> weights;
    ListDigraph::NodeMap <double> probs;
    ListDigraph::NodeMap <double> probs2;

    void clearMap(ListDigraph::NodeMap <double> &map);

public:
    IterativeRandomWalk(ListDigraph &cn, const ListDigraph::ArcMap <double> &weights);

    void Execute(ListDigraph::Node start_node, unsigned int max_path_length);

    double getProbability(ListDigraph::Node node);

    void getAllProbs(ListDigraph::NodeMap <double> &map);
};

#endif // ITERATIVERANDOMWALK_HPP
