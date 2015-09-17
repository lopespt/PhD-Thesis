//
// Created by Guilherme Wachs on 16/08/15.
//

#include <qthreadpool.h>
#include "Modularity.hpp"


bool Modularity::isSameClusters(const FeaturesComplexNetwork::Node &n1, const FeaturesComplexNetwork::Node &n2) {
    return clusters[n1] == clusters[n2];
}


float Modularity::execute() {
    float mod = 0;
    float m = cn.getNumArcs();
    for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it )
        for(FeaturesComplexNetwork::NodeIt it2(cn); it2 != INVALID; ++it2 ){
            double Aij = cn.arcExists(it, it2) ? cn.getLinkArcValue(it,it2).getWeight() : 0;
            double rand = deg[it]*deg[it2]/(2*m);
            mod += (Aij - rand) * isSameClusters(it, it2);
        }

    mod /= (2*m);

    return mod;
}

float Modularity::executeP(int threads){
    result = 0;
    it = FeaturesComplexNetwork::NodeIt(cn);
    mtx.unlock();
    QThreadPool pool;
    for(int i=0;i<threads;i++){
        pool.start(new ParcialSumProcess(*this));
    }
    pool.waitForDone();

    result /= (2*cn.getNumArcs());

    return result;
}

FeaturesComplexNetwork::Node Modularity::nextNode() {
    FeaturesComplexNetwork::Node n = it;
    ++it;
    return n;
}



void Modularity::ParcialSumProcess::run() {
    float pmod = 0;
    FeaturesComplexNetwork::Node it;
    puts("Thread started");
    float numArcs = m.cn.getNumArcs();

    while(true){
        m.mtx.lock();
        if(m.hasNextNode())
            it = m.nextNode();
        else {
            m.mtx.unlock();
            break;
        }
        //printf("%d\n", m.cn.id(m.it) );
        m.mtx.unlock();
        for(FeaturesComplexNetwork::NodeIt it2(m.cn); it2 != INVALID; ++it2 ){
            //printf("%d\n", m.cn.id(it2));
            double Aij = m.cn.arcExists(it, it2) ? m.cn.getLinkArcValue(it,it2).getWeight() : 0;
            double rand = m.deg[it]*m.deg[it2]/(2*numArcs);
            pmod += (Aij - rand) * m.isSameClusters(it, it2);
        }
    }

    m.mtx.lock();
    m.result+= pmod;
    m.mtx.unlock();
    printf("Finished thread: %f\n", pmod);

}

bool Modularity::hasNextNode() {
    return it != INVALID;
}
