#include "GraphUtilities.hpp"

GraphUtilities::GraphUtilities() {
}

ListDigraph::ArcMap<double>& GraphUtilities::getWeights(const FeaturesComplexNetwork &cn, ListDigraph::ArcMap <double> &weights) {
    for (FeaturesComplexNetwork::ArcIt it(cn); it != INVALID; ++it) {
        weights[it] = cn.getLinkArcValue(it).getWeight();
    }
    return weights;
}

void  GraphUtilities::normalizeOutDegrees(const FeaturesComplexNetwork &complexNetwork, const FeaturesComplexNetwork::ArcMap <double> &weights,
                                         FeaturesComplexNetwork::ArcMap <double> &output) {

    for (FeaturesComplexNetwork::NodeIt it(complexNetwork); it != INVALID; ++it) {
        //sum weights
        double totalOut = 0.0;

        for (ListDigraph::OutArcIt arc(complexNetwork, it); arc != INVALID; ++arc) {
            totalOut += weights[arc];
        }
        for (ListDigraph::OutArcIt arc(complexNetwork, it); arc != INVALID; ++arc) {
            if (totalOut != 0) {
                output[arc] = weights[arc] / totalOut;
            } else {
                output[arc] = 0;
            }
        }
    }
}

void  GraphUtilities::normalizeInDegrees(ListDigraph &complexNetwork, const ListDigraph::ArcMap <double> &weights,
                                          ListDigraph::ArcMap <double> &output) {

    for (ListDigraph::NodeIt it(complexNetwork); it != INVALID; ++it) {
        //sum weights
        double totalOut = 0.0;

        for (ListDigraph::InArcIt arc(complexNetwork, it); arc != INVALID; ++arc) {
            totalOut += weights[arc];
        }
        for (ListDigraph::InArcIt arc(complexNetwork, it); arc != INVALID; ++arc) {
            if (totalOut != 0) {
                output[arc] = weights[arc] / totalOut;
            } else {
                output[arc] = 0;
            }
        }
    }
}

void GraphUtilities::addAutoLoop(FeaturesComplexNetwork &cn, ListDigraph::ArcMap <double> &arcs, double value) {
    ArcLookUp<ListDigraph> look(cn);
    look.refresh();

    for (ListDigraph::NodeIt it(cn); it != INVALID; ++it) {
        ListDigraph::Arc arcId = look(it, it);

        if (arcId == INVALID)
           // arcId = cn.addArc(it, it, ); ??????

        arcs[arcId] = value;
    }
}

void GraphUtilities::normalizeWeights(ListDigraph &cn, const ListDigraph::ArcMap <double> &arcs,
                                      ListDigraph::ArcMap <double> &output) {

    ArcLookUp<ListDigraph> look(cn);
    look.refresh();

    double max = 0;

    for( ListDigraph::ArcIt it(cn); it != INVALID; ++it  ){
        if(arcs[it] > max){
            max = arcs[it];
        }
    }

    for( ListDigraph::ArcIt it(cn); it != INVALID; ++it  ){
            output[it] = output[it]/max;
    }
}
