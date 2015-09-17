//
// Created by Guilherme Wachs on 12/08/15.
//

#ifndef PHDTHESIS_COMPLEXNETWORKCONSTRUCTORP_H
#define PHDTHESIS_COMPLEXNETWORKCONSTRUCTORP_H


#include "ComplexNetworkConstructor.hpp"
#include <QRunnable>
#include <mutex>
#include <QMutex>

class ComplexNetworkConstructorP : public ComplexNetworkConstructor {

private:
    static unsigned int numP;
    static std::mutex mtx;

    QMutex mx;
    CoOcurrenceEquation *coOcurrenceEquationPolicy;
    int numThreads;

public:
    ComplexNetworkConstructorP(const ComplexNetworkConstructorP &other) : ComplexNetworkConstructor(other.cn,
                                                                                                    other.reader,
                                                                                                    other.extractors,
                                                                                                    other.coOcurrenceEquationPolicy),
                                                                          coOcurrenceEquationPolicy(
                                                                                  other.coOcurrenceEquationPolicy),
                                                                          numThreads(other.numThreads) {

    }

    ComplexNetworkConstructorP(FeaturesComplexNetwork &cn, DatabaseReader &reader,
                               const QList<const FeatureFactoryAbstract *> &extractors, int numThreads,
                               CoOcurrenceEquation *coOcurrenceEquationPolicy = NULL) : ComplexNetworkConstructor(cn,
                                                                                                                  reader,
                                                                                                                  extractors,
                                                                                                                  coOcurrenceEquationPolicy),
                                                                                        coOcurrenceEquationPolicy(
                                                                                                coOcurrenceEquationPolicy),
                                                                                        numThreads(numThreads) { }

    virtual void build() override;

    class ConstructorTask : public QRunnable {
    private:
        ComplexNetworkConstructorP &constructor;
    public:
        ConstructorTask(ComplexNetworkConstructorP &constructor);
        virtual void run() override;
    };

private:

protected:
    virtual void makeCoOccurrences(QLinkedList<FeatureAbstractPtr> &features, QList<int> &regionsIds) override;
};


#endif //PHDTHESIS_COMPLEXNETWORKCONSTRUCTORP_H

