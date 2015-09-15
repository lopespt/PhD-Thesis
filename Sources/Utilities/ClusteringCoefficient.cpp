//
// Created by Guilherme Wachs on 25/08/15.
//

#include "ClusteringCoefficient.h"
#include <vector>

float ClusteringCoefficient::compute(const FeaturesComplexNetwork::Node &node) {

    std::vector<FeaturesComplexNetwork::Node> list;
    for( FeaturesComplexNetwork::OutArcIt it(cn, node); it != INVALID; ++it ){
        list.insert(list.end(), cn.target(it));
    }
    //for( FeaturesComplexNetwork::InArcIt it(cn, node); it != INVALID; ++it ){
    //    list.insert(list.end(), cn.source(it));
    //}

    float sum=0;
    for(FeaturesComplexNetwork::Node i : list){
        for(FeaturesComplexNetwork::Node j : list){
            if(i!=j && cn.arcExists(i,j)){
                sum+=weights[cn.getArc(i,j)];
            }
        }
    }


    return sum/(list.size()*(list.size()-1));
}
