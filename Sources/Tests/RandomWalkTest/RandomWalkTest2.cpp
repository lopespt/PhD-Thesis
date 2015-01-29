#include "RandomWalkTest2.hpp"

#include <Utilities/CachedComplexNetwork.hpp>
#include <Utilities/IterativeRandomWalk.hpp>
#include <Utilities/RandomWalk.hpp>
RandomWalkTest2::RandomWalkTest2()
{


}

void RandomWalkTest2::execute(){

    CachedComplexNetwork<int, double> net;

    net.addNode(1);
    net.addNode(2);
    net.addNode(3);
    net.addNode(4);

    net.addEdge(net.getNodeId(1), net.getNodeId(4), 0.5);
    net.addEdge(net.getNodeId(1), net.getNodeId(2), 0.5);
    net.addEdge(net.getNodeId(1), net.getNodeId(3), 0.5);
    net.addEdge(net.getNodeId(3), net.getNodeId(2), 0.5);
    CachedComplexNetwork<int, double> net2 = RandomWalk::addAutoLoop(net);
    net2 = RandomWalk::normalizeGraph(net2);

    for(auto n = net2.Begin(); n != net2.End(); n++){
        for(auto e = n.EdgesBegin(); e!= n.EdgesEnd(); e++){
            //printf("%d -> %d = %f\n", *net2.getNode(e.getFromNodeId()), *net2.getNode(e.getToNodeId()), *e);
        }
    }


    printf("passei\n");

    IterativeRandomWalk w(&net2);
    w.Execute(1,5);
    double sum  = 0;
    foreach(double d, w.getAllProbs()){
        sum += d;
        printf("%f\n", d);
    }
    printf("sum  = %f;", sum);

}
