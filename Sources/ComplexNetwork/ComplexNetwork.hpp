#ifndef COMPLEXNETWORK_HPP
#define COMPLEXNETWORK_HPP

#include <assert.h>
#include <mutex>
#include <lemon/list_graph.h>

using namespace lemon;

template<typename N, typename E>
class ComplexNetwork : public ListDigraph {
private:
protected:
    mutable std::mutex mtxN;
    mutable std::mutex mtxE;
    ListDigraph::NodeMap <N> nodes;
    ListDigraph::ArcMap <E> arcs;
    DynArcLookUp<ListDigraph> lookup;

public:
    ComplexNetwork(const ComplexNetwork<N, E> &other) : nodes(*this), arcs(*this), lookup(*this) {
        digraphCopy(other, *this).nodeMap(other.nodes, this->nodes).arcMap(other.arcs, this->arcs).run();
    }

    ComplexNetwork() : nodes(*this), arcs(*this), lookup(*this) {
    }

    ListDigraph::Node addNode() {
        mtxN.lock();
        auto ret = ListDigraph::addNode();
        mtxN.unlock();
        return ret;
    }

    ListDigraph::Node addNode(const N &val) {
        mtxN.lock();
        ListDigraph::Node n = ListDigraph::addNode();
        nodes[n] = val;
        mtxN.unlock();
        return n;
    }

    ListDigraph::Arc addArc(ListDigraph::Node f, ListDigraph::Node t) {
        mtxE.lock();
        auto ret = ListDigraph::addArc(f, t);
        mtxE.unlock();
        return ret;
    }

    ListDigraph::Arc addArc(ListDigraph::Node f, ListDigraph::Node t, const E &val) {
        mtxE.lock();
        ListDigraph::Arc a = ListDigraph::addArc(f, t);
        arcs[a] = val;
        mtxE.unlock();
        return a;
    }

    Arc getArc(Node a, Node b) const{
        //mtxE.lock();
        Arc i = lookup(a, b);
        assert(this->valid(i));
        //mtxE.unlock();
        return lookup(a, b);
    }

    E &getArcValue(Arc a) {
        //mtxE.lock();
        assert(valid(a));
        auto &ret = arcs[a];
        //mtxE.unlock();
        return ret;
    }

    const E &getArcValue(Arc a) const {
        //mtxE.lock();
        assert(valid(a));
        auto &ret = arcs[a];
        //mtxE.unlock();
        return ret;
    }

    E &getArcValue(int a) {
        //mtxE.lock();
        assert(valid(arcFromId(a)));
        auto &ret = arcs[this->arcFromId(a)];
        //mtxE.unlock();
        return ret;
    }

    const E &getArcValue(int a) const {
        //mtxE.lock();
        assert(valid(arcFromId(a)));
        auto &ret = arcs[this->arcFromId(a)];
        //mtxE.unlock();
        return ret;
    }


    inline E &getArcValue(Node a, Node b) {
        //mtxE.lock();
        assert(valid(lookup(a, b)));
        auto &ret = arcs[lookup(a, b)];
        //mtxE.unlock();
        return ret;
    }

    N &getNode(Node n) {
        //mtxN.lock();
        assert(valid(n));
        auto &ret = nodes[n];
        //mtxN.unlock();
        return ret;
    }

    bool arcExists(const Node &a,const Node &b) const{
        //mtxE.lock();
        auto ret = valid(this->lookup(a, b));
        //mtxE.unlock();
        return ret;
    }

    int getNumNodes() {
        return countNodes(*this);
    }

    int getNumArcs() {
        return countArcs(*this);
    }


    const ListDigraph::ArcMap <E> &getArcMap() const {
        return this->arcs;
    }


};

#endif // COMPLEXNETWORK_HPP
