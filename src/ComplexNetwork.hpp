
#ifndef COMPLEX_NETWORK__CPP
#define COMPLEX_NETWORK__CPP

#include <stdio.h>
#include "Node.hpp"
#include "Edge.hpp"
#include <list>

/**
 * Rede Complexa
 * **/
template <class NODE_TYPE, class EDGE_TYPE>
class ComplexNetwork{

    private:
        std::list<Node<NODE_TYPE>* > nodes;
        std::list<Edge<EDGE_TYPE,NODE_TYPE>* > edges;


    public:
        ComplexNetwork();
        void addNode(Node<NODE_TYPE> *);

};

#endif
