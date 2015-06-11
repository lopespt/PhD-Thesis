#ifndef CLOSERNODESGUESSER_HPP
#define CLOSERNODESGUESSER_HPP

#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/IterativeRandomWalk.hpp>
#include <QList>

class CloserNodesGuesser {
private:
    FeaturesComplexNetwork cn;
    IterativeRandomWalk &rw;
public:
    typedef struct {
        FeaturesComplexNetwork::Node node;
        float probability;
    } NodeProbability;

    CloserNodesGuesser(const FeaturesComplexNetwork &cn, IterativeRandomWalk &rw);

    QList<NodeProbability> guessNodes(const QList<FeatureAbstractPtr> &features) const;

    QList<NodeProbability> doIterativeRandomWalk(const QList<FeatureAbstractPtr> &hints, unsigned int walks) const;


    ~CloserNodesGuesser();


};

#endif // CLOSERNODESGUESSER_HPP
