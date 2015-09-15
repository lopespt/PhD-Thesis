//
// Created by Guilherme Wachs on 12/08/15.
//

#ifndef PHDTHESIS_COMPLEXNETWORKCONSTRUCTORP_H
#define PHDTHESIS_COMPLEXNETWORKCONSTRUCTORP_H


#include "ComplexNetworkConstructor.hpp"
#include <QRunnable>
#include <mutex>
#include <QMutex>

class ComplexNetworkConstructorP : public ComplexNetworkConstructor, public QRunnable {

private:
    static unsigned int numP;
    static std::mutex mtx;

    QMutex mx;
    CoOcurrenceEquation *coOcurrenceEquationPolicy;
    QHash<FeatureAbstractPtr, FeaturesComplexNetwork::Node> index;
    QHash<FeatureAbstractPtr, FeaturesComplexNetwork::Node>* cache;
    int numThreads;

public:
    ComplexNetworkConstructorP(const ComplexNetworkConstructorP &other):ComplexNetworkConstructor(other.cn, other.reader,
                                                                                                  other.extractors,
                                                                                                  other.coOcurrenceEquationPolicy), coOcurrenceEquationPolicy(other.coOcurrenceEquationPolicy), cache(other.cache), numThreads(other.numThreads){

    }

    ComplexNetworkConstructorP(FeaturesComplexNetwork &cn, DatabaseReader &reader,
                               const QList<const FeatureFactoryAbstract *> &extractors, int numThreads,
                               CoOcurrenceEquation *coOcurrenceEquationPolicy=NULL, QHash<FeatureAbstractPtr, FeaturesComplexNetwork::Node> *cache=NULL) : ComplexNetworkConstructor(cn, reader,
                                                                                                           extractors,
                                                                                                           coOcurrenceEquationPolicy), coOcurrenceEquationPolicy(coOcurrenceEquationPolicy), cache(cache), numThreads(numThreads) {
    setAutoDelete(true);
    }


    virtual void build() override;

    virtual void run() override;

private:

protected:
    virtual void makeCoOccurrences(QLinkedList<FeatureAbstractPtr> &features, QList<int> &regionsIds) override;
};


#endif //PHDTHESIS_COMPLEXNETWORKCONSTRUCTORP_H

