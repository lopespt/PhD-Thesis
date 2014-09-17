
#include "Edge.hpp"

/**
 * Por padrão as arestas são direcionadas
 * \param  from Nó de saída
 * \param to  Nó de entrada
 */
template<class ATTR_TYPE, class NODE_TYPE>
Edge<ATTR_TYPE,NODE_TYPE>::Edge(Node<NODE_TYPE>* from, Node<NODE_TYPE>* to){
    this->from = from;
    this->to = to;
}

/**
 * Por padrão as arestas são direcionadas
 * \param  from Nó de saída
 * \param to  Nó de entrada
 * \param attribute Atributo da aresta
 */
template<class ATTR_TYPE, class NODE_TYPE>
Edge<ATTR_TYPE,NODE_TYPE>::Edge(Node<NODE_TYPE>* from, Node<NODE_TYPE>* to, ATTR_TYPE attribute){
    this->from = from;
    this->to = to;
    this->attribute = attribute;
}


template<class ATTR_TYPE, class NODE_TYPE>
ATTR_TYPE Edge<ATTR_TYPE, NODE_TYPE>::getAttribute(){
    return this->attribute;
}

template<class ATTR_TYPE, class NODE_TYPE>
void Edge<ATTR_TYPE, NODE_TYPE>::setAttribute(ATTR_TYPE attr){
    this->attribute = attr;
}


