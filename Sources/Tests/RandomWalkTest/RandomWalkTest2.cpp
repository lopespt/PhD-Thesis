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
    IterativeRandomWalk walk(net, weights);
    walk.Execute(na,1);


    for (auto n = ComplexNetwork<int, double>::NodeIt(net) ; n != INVALID; ++n) {
        for (auto e = ComplexNetwork<int, double>::NodeIt(net) ; e != INVALID; ++e) {
            printf("%d -> %d = %f\n", net.getNode(n), net.getNode(e), walk.getProbability(e) );
        }
    }


    printf("passei\n");


}
