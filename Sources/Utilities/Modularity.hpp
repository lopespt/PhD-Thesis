//
// Created by Guilherme Wachs on 16/08/15.
//

#ifndef PHDTHESIS_MODULARITY_HPP
#define PHDTHESIS_MODULARITY_HPP


#include <qthread.h>
#include "FeaturesComplexNetwork.hpp"
#include "Degrees.h"
#include <mutex>
#include <QRunnable>

using namespace std;

class Modularity {
    FeaturesComplexNetwork &cn;
    const FeaturesComplexNetwork::NodeMap<int> &clusters;
    FeaturesComplexNetwork::NodeMap<double> deg;
    mutex mtx;
    FeaturesComplexNetwork::NodeIt it;
    float result=0;
private:
    bool isSameClusters(const FeaturesComplexNetwork::Node &n1,const FeaturesComplexNetwork::Node &n2);
    FeaturesComplexNetwork::Node nextNode();
    bool hasNextNode();

public:
    Modularity(FeaturesComplexNetwork &cn, const FeaturesComplexNetwork::NodeMap<int> &clusters): cn(cn), clusters(clusters), deg(cn){
        FeaturesComplexNetwork::ArcMap<double> weights(cn);
        GraphUtilities::getWeights(cn, weights);
        GraphUtilities::normalizeOutDegrees(cn, weights, weights);
        GraphUtilities::addAutoLoop(cn, weights, 1);
        GraphUtilities::normalizeOutDegrees(cn, weights, weights);
        Degrees::computeDegreeMap(cn, weights, deg);
        result=0;
    }

    float executeP(int threads);
    float execute();

    class ParcialSumProcess : public QRunnable{
    private:
        Modularity &m;
    public:
        ParcialSumProcess(Modularity &m): m(m){}

    private:
        virtual void run() override;
    };



};


#endif //PHDTHESIS_MODULARITY_H
