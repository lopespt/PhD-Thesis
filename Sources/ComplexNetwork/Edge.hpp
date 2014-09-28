
#ifndef EDGE__H
#define EDGE__H

template <class NODE_TYPE, class EDGE_TYPE>
class Edge;

template <class NODE_TYPE, class EDGE_TYPE>
class ComplexNetwork;

#include <Node.hpp>
#include <ComplexNetwork.hpp>


/*
 * Esta classe representa uma aresta da rede complexa. Ela contém dois
 * ponteiros para nós (from e to) e um atributo.
 * Essa é uma classe gabarito. ATTR_TYPE é o tipo da aresta e NODE_TYPE
 * representa o tipo do nó
 */
template <class NODE_TYPE, class EDGE_TYPE>
class Edge{
    private:
        Node<NODE_TYPE, EDGE_TYPE>* from;
        Node<NODE_TYPE, EDGE_TYPE>* to;
        EDGE_TYPE attribute;
        static unsigned long int num_edges;

    public:
        EDGE_TYPE getAttribute();
        void setAttribute(EDGE_TYPE attr);
        Edge(Node<NODE_TYPE, EDGE_TYPE>* from, Node<NODE_TYPE, EDGE_TYPE>* to);
        Edge(Node<NODE_TYPE, EDGE_TYPE>* from, Node<NODE_TYPE, EDGE_TYPE>* to, EDGE_TYPE attribute);
        ~Edge();

        friend class ComplexNetwork<NODE_TYPE, EDGE_TYPE>;
};


template <class NODE_TYPE, class EDGE_TYPE>
unsigned long int Edge<NODE_TYPE, EDGE_TYPE>::num_edges=0;

/**
 * Por padrão as arestas são direcionadas
 * \param  from Nó de saída
 * \param to  Nó de entrada
 */
template <class NODE_TYPE, class EDGE_TYPE>
Edge<NODE_TYPE,EDGE_TYPE>::Edge(Node<NODE_TYPE, EDGE_TYPE>* from, Node<NODE_TYPE, EDGE_TYPE>* to){
    num_edges++;
    printf("num_edges = %lu\n", num_edges);
    this->from = from;
    this->to = to;
}


template <class NODE_TYPE, class EDGE_TYPE>
Edge<NODE_TYPE,EDGE_TYPE>::~Edge(){
    num_edges--;
    printf("num_edges = %lu\n", num_edges);
} 
/**
 * Por padrão as arestas são direcionadas
 * \param  from Nó de saída
 * \param to  Nó de entrada
 * \param attribute Atributo da aresta
 */
template <class NODE_TYPE, class EDGE_TYPE>
Edge<NODE_TYPE,EDGE_TYPE>::Edge(Node<NODE_TYPE, EDGE_TYPE>* from, Node<NODE_TYPE, EDGE_TYPE>* to, EDGE_TYPE attribute){
    num_edges++;
    printf("num_edges = %lu\n", num_edges);
    this->from = from;
    this->to = to;
    this->attribute = attribute;
}


template <class NODE_TYPE, class EDGE_TYPE>
EDGE_TYPE Edge<NODE_TYPE,EDGE_TYPE>::getAttribute(){
    return this->attribute;
}

template <class NODE_TYPE, class EDGE_TYPE>
void Edge<NODE_TYPE, EDGE_TYPE>::setAttribute(EDGE_TYPE attr){
    this->attribute = attr;
}




#endif
