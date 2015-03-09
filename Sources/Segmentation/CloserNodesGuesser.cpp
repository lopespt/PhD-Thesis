#include "CloserNodesGuesser.hpp"
#include <Utilities/GraphUtilities.hpp>

CloserNodesGuesser::CloserNodesGuesser(const FeaturesComplexNetwork& cn, IterativeRandomWalk &rw):
    cn(cn),
    rw(rw)
{
}


QList<CloserNodesGuesser::NodeProbability> CloserNodesGuesser::doIterativeRandomWalk(const QList<FeatureAbstractPtr >& hints, int walks) const{

    QList<FeaturesComplexNetwork::Node> ids;
    for(const FeatureAbstractPtr &s: hints){
        FeaturesComplexNetwork::Node id = cn.getNodeFromFeature(s);
        if( cn.valid(id))
            ids.append(id);
        else
            puts("Node not found");

    }

    FeaturesComplexNetwork::NodeMap<double> final(cn);
    GraphUtilities::fillMap(cn, final, 1.0);


    foreach(FeaturesComplexNetwork::Node id, ids){
        rw.Execute(id, walks);
        FeaturesComplexNetwork::NodeMap<double> probs(cn);
        rw.getAllProbs(probs);
        for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it){
                final[it] = final[it]  *(1 - probs[it]);
        }
    }

    QVector<FeaturesComplexNetwork::Node> order;
    for(FeaturesComplexNetwork::NodeIt i(cn); i != INVALID;++i){
        final[i] = 1 - final[i];
        order.append(i);
    }

    qSort(order.begin(), order.end(), [&](const FeaturesComplexNetwork::Node &a, const FeaturesComplexNetwork::Node &b){
        return final[b] < final[a];
    });

    QList<NodeProbability> retorno;
    for(int i=0;i<order.size();i++){
        NodeProbability n;
        n.node = order[i];
        n.probability = final[order[i]];
    }

    return  retorno;
}

QList<CloserNodesGuesser::NodeProbability> CloserNodesGuesser::guessNodes(const QList<FeatureAbstractPtr>& features) const{
    return doIterativeRandomWalk(features, 2);
}

CloserNodesGuesser::~CloserNodesGuesser()
{

}

