#ifndef COMPLEXNETWORK_HPP
#define COMPLEXNETWORK_HPP

#include <QHash>
#include <QPair>
#include <QMap>
#include <QFile>
#include <QSet>
#include <assert.h>
#include <lemon/list_graph.h>

using namespace lemon;

template <typename N, typename E>
class ComplexNetwork : public ListDigraph
{
protected:
    ListDigraph::NodeMap<N> nodes;
    ListDigraph::ArcMap<E>  arcs;
    DynArcLookUp<ListDigraph> lookup;
public:
    ComplexNetwork():nodes(*this), arcs(*this), lookup(*this){
    }

    ListDigraph::Node addNode(){
        return ListDigraph::addNode();
    }

    ListDigraph::Node addNode(const N& val){
        ListDigraph::Node n = ListDigraph::addNode();
        nodes[n] = val;
        return n;
    }

    ListDigraph::Arc addArc( ListDigraph::Node f, ListDigraph::Node t){
        return ListDigraph::addArc(f,t);
    }

    ListDigraph::Arc addArc( ListDigraph::Node f, ListDigraph::Node t, const E& val){
        ListDigraph::Arc a = ListDigraph::addArc(f, t);
        arcs[a] = val;
        return a;
    }

    Arc getArc(Node a, Node b){
        Arc i = lookup(a,b);
        assert(this->valid(i));

        return lookup(a,b);
    }

    E& getArcValue(Arc a){
        assert( valid(a) );
        return arcs[a];
    }

    E& getArcValue(int a){
        assert( valid(arcFromId(a)) );
        return arcs[ this->arcFromId(a) ];
    }

    E& getArcValue(Node a, Node b){
        assert( valid(lookup(a,b)) );
        return arcs[ lookup(a,b) ];
    }

    N& getNode(Node n){
        assert( valid(n) );
        return nodes[n];
    }

    bool arcExists(Node a, Node b){
        return valid(this->lookup(a,b));
    }

    int getNumNodes(){
        return countNodes(*this);
    }

    int getNumArcs(){
        return countArcs(*this);
    }


    const ListDigraph::ArcMap<E>&  getArcMap()const {
        return this->arcs;
    }


};

#endif // COMPLEXNETWORK_HPP
