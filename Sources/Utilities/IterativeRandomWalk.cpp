#include "IterativeRandomWalk.hpp"
#include "GraphUtilities.hpp"

IterativeRandomWalk::IterativeRandomWalk(ListDigraph &cn, const ListDigraph::ArcMap <double> &weights) :
        cn(cn), weights(cn), probs(cn), probs2(cn) {

    clearMap(probs);

    GraphUtilities::normalizeOutDegrees(this->cn, weights, this->weights);
    GraphUtilities::addAutoLoop(this->cn, this->weights);
    GraphUtilities::normalizeOutDegrees(this->cn, this->weights, this->weights);

}

void IterativeRandomWalk::clearMap(ListDigraph::NodeMap < double > &map) {
    for (ListDigraph::NodeIt it(cn); it != INVALID; ++it) {
        map[it] = 0;
    }
}


void IterativeRandomWalk::Execute(ListDigraph::Node start_node, unsigned int max_path_length) {
    clearMap(probs);

    probs[start_node] = 1;
    for (unsigned int i = 0; i < max_path_length; i++) {
        clearMap(probs2);
        for (ListDigraph::NodeIt node(cn); node != INVALID; ++node) {
            if (probs[node]) {
                for (ListDigraph::OutArcIt edge(cn, node); edge != INVALID; ++edge) {
                    probs2[cn.target(edge)] += probs[node] * weights[edge];
                }
            }
        }

        GraphUtilities::copyMap(cn, probs2, probs);
    }
    //probs[start_node] = 0;
}

double IterativeRandomWalk::getProbability(ListDigraph::Node node) {
    return probs[node];
}

void IterativeRandomWalk::getAllProbs(ListDigraph::NodeMap < double > &map) {
    GraphUtilities::copyMap(cn, probs, map);
}
