//
// Created by Guilherme Wachs on 21/10/15.
//

#include "ClusteringCoefficientTask.hpp"
#include "ClusteringCoefficient.hpp"

ClusteringCoefficientTask::ClusteringCoefficientTask(ClusteringCoefficient *parent ,const FeaturesComplexNetwork &cn,
                                                     const FeaturesComplexNetwork::ArcMap<double>& weights,
                                                     QList<FeaturesComplexNetwork::Node> nodes): parent(parent) ,cn(cn), weights(weights), nodes(nodes) {

    this->setAutoDelete(true);

}


void ClusteringCoefficientTask::run() {
//    int i=0;
  //  int size = nodes.size();
    QList<NodeCC> ccs;
    for(const auto &node: nodes){
        ccs.append(NodeCC{ node, computeCC(node) });
        //printf("%5d | %5d (%3d)\n",i++,size,(int)(i*1./size*100));
    }
    parent->mut.lock();
    parent->te.tick(ccs.size());
    parent->ccs.append(ccs);
    parent->te.print();
    parent->mut.unlock();

}

float ClusteringCoefficientTask::computeCC(ListDigraphBase::Node node) const {

    float sum=0;
    int total=0;
    for( FeaturesComplexNetwork::OutArcIt it(cn,node); it != INVALID; ++it){
        total++;
        for( FeaturesComplexNetwork::OutArcIt it2(cn,node); it2 != INVALID; ++it2) {
            FeaturesComplexNetwork::Node a = cn.target(it);
            FeaturesComplexNetwork::Node b = cn.target(it2);

            if(cn.arcExists(a,b,Link::LinkType::OtherLabel))
                sum += weights[cn.getArc(a,b,Link::LinkType::OtherLabel)];

            if(cn.arcExists(b,a,Link::LinkType::OtherLabel))
                sum += weights[cn.getArc(b,a,Link::LinkType::OtherLabel)];
        }
    }

    if(total<=1){
        return 0;
    }

    return sum/(total*(total-1));
}
