#include "IterativeRandomWalk.hpp"
#include "GraphUtilities.hpp"


IterativeRandomWalk::IterativeRandomWalk(const FeaturesComplexNetwork &cn):
    cn(cn),weights(cn), probs(cn), probs2(cn)
{
    clearMap(probs);
    clearMap(weights);
}


IterativeRandomWalk::IterativeRandomWalk(const FeaturesComplexNetwork &cn, const ListDigraph::ArcMap <double> &weights) :
        cn(cn), weights(cn), probs(cn), probs2(cn) {

    clearMap(probs);

    GraphUtilities::normalizeOutDegrees(this->cn, weights, this->weights);
    //GraphUtilities::addAutoLoop(this->cn, this->weights);
    //GraphUtilities::normalizeOutDegrees(this->cn, weights, this->weights);

    /*
    GraphUtilities::normalizeInDegrees(this->cn, weights, this->weights);
    GraphUtilities::addAutoLoop(this->cn, this->weights);
    GraphUtilities::normalizeInDegrees(this->cn, this->weights, this->weights);
    */
}

void IterativeRandomWalk::clearMap(NodeMapDouble &ma ) {
    for (ListDigraph::NodeIt it(cn); it != INVALID; ++it) {
        ma[it] = 0;
    }
}

void IterativeRandomWalk::getAllProbs(NodeMapDouble &ma) {
    GraphUtilities::copyMap(cn, probs, ma);
}

void IterativeRandomWalk::Execute(ListDigraph::Node start_node, unsigned int max_path_length) {
    clearMap(probs);

    probs[start_node] = 1;
    for (unsigned int i = 0; i < max_path_length; i++) {
        clearMap(probs2);
        for (ListDigraph::NodeIt node(cn); node != INVALID; ++node) {
            if (probs[node] > 0) {
                for (ListDigraph::OutArcIt edge(cn, node); edge != INVALID; ++edge) {
                    probs2[cn.target(edge)] += probs[node] * weights[edge];
                }
                //probs2[node] += 0.2;
            }
        }

        GraphUtilities::copyMap(cn, probs2, probs);
    }
    //probs[start_node] = 0;
}

double IterativeRandomWalk::getProbability(ListDigraph::Node node) {
    return probs[node];
}

void IterativeRandomWalk::clearMap(ArcMapDouble &map) {
    for (ListDigraph::ArcIt it(cn); it != INVALID; ++it) {
        map[it] = 0;
    }
}

void IterativeRandomWalk::setWeights(ArcMapDouble &weights) {
    GraphUtilities::normalizeOutDegrees(this->cn, weights, this->weights);
    //GraphUtilities::addAutoLoop(this->cn, this->weights);
    //GraphUtilities::normalizeOutDegrees(this->cn, this->weights, this->weights);
}
