#include "GraphUtilities.hpp"
#include "CachedComplexNetwork.hpp"
#include <QHash>

GraphUtilities::GraphUtilities()
{
}

void GraphUtilities::getWeights(FeaturesComplexNetwork &cn, ListDigraph::ArcMap<double> &weights){
    for( FeaturesComplexNetwork::ArcIt it(cn); it != INVALID; ++it){
        weights[it] = cn.getArcValue(it).getWeight();
    }
}

void  GraphUtilities::normalizeOutDegrees(ListDigraph& complexNetwork, const ListDigraph::ArcMap<double> &weights, ListDigraph::ArcMap<double> &output){

    for( ListDigraph::NodeIt it(complexNetwork); it != INVALID; ++it){
        //sum weights
        double totalOut = 0.0;

        for( ListDigraph::OutArcIt arc(complexNetwork, it); arc != INVALID; ++arc){
                totalOut +=  weights[arc];
        }
        for( ListDigraph::OutArcIt arc(complexNetwork, it); arc != INVALID; ++arc){
            if(totalOut != 0)
                output[arc] = weights[arc] / totalOut;
            else{
                output[arc] = 0;
            }
        }
    }
}

void GraphUtilities::addAutoLoop(ListDigraph& cn, ListDigraph::ArcMap<double>& arcs, double value){
    ArcLookUp<ListDigraph> look(cn);
    look.refresh();

    for( ListDigraph::NodeIt it(cn); it != INVALID; ++it){
        ListDigraph::Arc arcId = look(it,it);

        if( arcId == INVALID )
            arcId = cn.addArc(it,it);

        arcs[arcId] = value;
    }
}
