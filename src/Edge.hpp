
#ifndef EDGE__H
#define EDGE__H

template <class ATTR_TYPE, class NODE_TYPE>

class Edge;
#include "Node.hpp"


/*
 * Esta classe representa uma aresta da rede complexa. Ela contém dois
 * ponteiros para nós (from e to) e um atributo.
 * Essa é uma classe gabarito. ATTR_TYPE é o tipo da aresta e NODE_TYPE
 * representa o tipo do nó
 */
template <class ATTR_TYPE, class NODE_TYPE>
class Edge{
    private:
        Node<NODE_TYPE>* from;
        Node<NODE_TYPE>* to;
        ATTR_TYPE attribute;

    public:
        ATTR_TYPE getAttribute();
        void setAttribute(ATTR_TYPE attr);
        Edge(Node<NODE_TYPE>* from, Node<NODE_TYPE>* to);
        Edge(Node<NODE_TYPE>* from, Node<NODE_TYPE>* to, ATTR_TYPE attribute);
};




#endif
