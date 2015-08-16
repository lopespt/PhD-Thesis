//
// Created by Guilherme Wachs on 13/08/15.
//

#ifndef PHDTHESIS_MODULARITY_H
#define PHDTHESIS_MODULARITY_H

#include <lemon/list_graph.h>
#include "GraphUtilities.hpp"

using namespace lemon;

class Modularity {
private:
    FeaturesComplexNetwork &cn;
    ListDigraph::ArcMap<double> weights;
    ListDigraph::NodeMap<float> outDeg;
public:
    Modularity(FeaturesComplexNetwork &cn, const ListDigraph::ArcMap <double> &weights): cn(cn), weights(cn), outDeg(cn) {
        GraphUtilities::normalizeOutDegrees(this->cn, weights, this->weights);
        GraphUtilities::addAutoLoop(this->cn, this->weights);
        GraphUtilities::normalizeOutDegrees(this->cn, this->weights, this->weights);
        //GraphUtilities::copyMap(this->cn, weights, this->weights);

    }
    float execute();


};


#endif //PHDTHESIS_MODULARITY_H
