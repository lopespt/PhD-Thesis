#include "RandomWalkTest2.hpp"
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/IterativeRandomWalk.hpp>
#include <Utilities/GraphUtilities.hpp>

RandomWalkTest2::RandomWalkTest2() {


}

void RandomWalkTest2::execute() {

    ComplexNetwork <int, double> net;

    const ListDigraphBase::Node &na = net.addNode(1);
    const ListDigraphBase::Node &nb = net.addNode(2);
    const ListDigraphBase::Node &nc = net.addNode(3);
    const ListDigraphBase::Node &nd = net.addNode(4);

    net.addArc(na , nd, 100);
    net.addArc(nc, nb, 0.5);
    net.addArc(nb, nc, 0.5);
    net.addArc(nc, nb, 0.5);
    ListDigraph::ArcMap<double> weights(net) ;
    GraphUtilities::copyMap(net, net.getArcMap(), weights);

    printf("passei\n");


}
