//
// Created by Guilherme Wachs on 15/09/15.
//

#ifndef PHDTHESIS_DYNLINKLOOKUP_HPP
#define PHDTHESIS_DYNLINKLOOKUP_HPP

#include <lemon/core.h>
#include <lemon/list_graph.h>
#include "Link.hpp"

using namespace lemon;

class DynLinkLookUp : public DynArcLookUp {

private:
    QHash<FeatureAbstractPtr, Node> featureIndex;

public:
    DynLinkLookUp(const FeaturesComplexNetwork &g): DynArcLookUp(g) { }


};


#endif //PHDTHESIS_DYNLINKLOOKUP_HPP
