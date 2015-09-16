//
// Created by Guilherme Wachs on 15/09/15.
//

#ifndef PHDTHESIS_DYNLINKLOOKUP_HPP
#define PHDTHESIS_DYNLINKLOOKUP_HPP

#include <lemon/core.h>
#include <lemon/list_graph.h>
#include <vector>
class FeaturesComplexNetwork;
using namespace lemon;
using namespace std;

class DynLinkLookUp {

private:
    typedef typename AlterationNotifier<ListDigraph, ListDigraph::Arc>::ObserverBase Parent;
    typedef AlterationNotifier<ListDigraph, ListDigraph::Arc> Notifier;

public:
    DynLinkLookUp(const FeaturesComplexNetwork &g);

protected:


public:
};


#endif //PHDTHESIS_DYNLINKLOOKUP_HPP
