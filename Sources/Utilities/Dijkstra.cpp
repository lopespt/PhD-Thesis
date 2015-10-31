//
// Created by Guilherme Wachs on 30/10/15.
//

#include "Dijkstra.hpp"

Dijkstra::Dijkstra(const FeaturesComplexNetwork &cn) : cn(cn)  {
}
void Dijkstra::reset() {
    for(NodeIt it(cn); it != INVALID; ++it){
        ind[it]= dists.push(INFINITE);
        revInd[ ind[it] ] = it;
    }
}

FeaturesComplexNetwork::NodeMap<float> Dijkstra::run(const Dijkstra::Node& start) {
    reset();
    dists.decrease_key(ind[start],0);

    while(!dists.empty()){
        auto exp = dists.extract_min();
        auto from = revInd[exp];
        puts("0");
        for(OutArcIt it(cn, from); it != INVALID; ++it){
            auto to = cn.target(it);
            puts("1");
            if( cn.arcExists(from, to, Link::LinkType::OtherLabel ) ) {
                puts("2");
                relax(from, cn.target(it), 1.0f/cn.getLinkArcValue(from,to, Link::LinkType::OtherLabel).getWeight());
                puts("3");
            }
        }
    }
}

void Dijkstra::relax(const Dijkstra::Node &a, const Dijkstra::Node &b, float w) {
    float newWeight = ind[a]->key + w;
    if( ind[b]->key  > newWeight ){
        dists.decrease_key(ind[b], newWeight);
    }
}
