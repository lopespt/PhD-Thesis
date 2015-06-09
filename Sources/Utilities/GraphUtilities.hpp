#ifndef RANDOMWALK_HPP
#define RANDOMWALK_HPP

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/FeaturesComplexNetwork.hpp>

class GraphUtilities {
private:
    GraphUtilities();

public:
    template<typename T>
    static ListDigraph::NodeMap <T> &copyMap(const ListDigraph &graph, const ListDigraph::NodeMap <T> &from,
                                             ListDigraph::NodeMap <T> &to);

    template<typename T>
    static ListDigraph::ArcMap <T> &copyMap(const ListDigraph &graph, const ListDigraph::ArcMap <T> &from,
                                            ListDigraph::ArcMap <T> &to);

    template<typename T>
    static ListDigraph::NodeMap <T> &fillMap(const ListDigraph &graph, ListDigraph::NodeMap <T> &map, const T &value);

    template<typename T>
    static ListDigraph::ArcMap <T> &fillMap(const ListDigraph &graph, ListDigraph::ArcMap <T> &map, const T &value);

    static void getWeights(const FeaturesComplexNetwork &cn, ListDigraph::ArcMap <double> &weights);

    static void normalizeOutDegrees(ListDigraph &complexNetwork, const ListDigraph::ArcMap <double> &weights,
                                    ListDigraph::ArcMap <double> &output);

    static void addAutoLoop(ListDigraph &cn, ListDigraph::ArcMap <double> &arcs, double value = 1);
};


template<typename T>
ListDigraph::NodeMap <T> &GraphUtilities::copyMap(const ListDigraph &graph, const ListDigraph::NodeMap <T> &from,
                                                  ListDigraph::NodeMap <T> &to) {
    for (ListDigraph::NodeIt it(graph); it != INVALID; ++it) {
        to[it] = from[it];
    }
    return to;
}

template<typename T>
ListDigraph::ArcMap <T> &GraphUtilities::copyMap(const ListDigraph &graph, const ListDigraph::ArcMap <T> &from,
                                                 ListDigraph::ArcMap <T> &to) {
    for (ListDigraph::ArcIt it(graph); it != INVALID; ++it) {
        to[it] = from[it];
    }
    return to;
}

template<typename T>
ListDigraph::NodeMap <T> &GraphUtilities::fillMap(const ListDigraph &graph, ListDigraph::NodeMap <T> &map,
                                                  const T &value) {
    for (ListDigraph::NodeIt it(graph); it != INVALID; ++it) {
        map[it] = value;
    }
    return map;
}

template<typename T>
ListDigraph::ArcMap <T> &GraphUtilities::fillMap(const ListDigraph &graph, ListDigraph::ArcMap <T> &map,
                                                 const T &value) {
    for (ListDigraph::ArcIt it(graph); it != INVALID; ++it) {
        map[it] = value;
    }
    return map;
}

#endif // RANDOMWALK_HPP
