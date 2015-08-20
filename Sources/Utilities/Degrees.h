//
// Created by Guilherme Wachs on 16/08/15.
//

#ifndef PHDTHESIS_DEGREES_H
#define PHDTHESIS_DEGREES_H


#include <lemon/list_graph.h>
#include "GraphUtilities.hpp"

class Degrees {
private:
public:
    static void computeDegreeMap(const ListDigraph &cn, const ListDigraph::ArcMap<double> &weights, ListDigraph::NodeMap<double> &deg){
        for( ListDigraph::ArcIt it(cn); it != INVALID; ++it ){
            double weight = weights[it];
            deg[cn.source(it)] += weight;
            deg[cn.target(it)] += weight;
        }
    }

    static void computeOutDegreeMap(const ListDigraph &cn, const ListDigraph::ArcMap<double> &weights, ListDigraph::NodeMap<double> &deg){
        for( ListDigraph::ArcIt it(cn); it != INVALID; ++it ){
            double weight = weights[it];
            deg[cn.source(it)] += weight;
        }
    }

    static void computeInDegreeMap(const ListDigraph &cn, const ListDigraph::ArcMap<double> &weights, ListDigraph::NodeMap<double> &deg){
        for( ListDigraph::ArcIt it(cn); it != INVALID; ++it ){
            double weight = weights[it];
            deg[cn.target(it)] += weight;
        }
    }
};


#endif //PHDTHESIS_DEGREES_H
