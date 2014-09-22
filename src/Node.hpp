

#ifndef NODE__H
#define NODE__H
template <class NODE_TYPE, class EDGE_TYPE>
class Node;
#include "Edge.hpp"
#include <list>

template <class NODE_TYPE, class EDGE_TYPE>
class Node{
    private:
        int _id;
        NODE_TYPE attribute;
        //std::list<Edge<NODE_TYPE, EDGE_TYPE>* > edges;
    public:
        NODE_TYPE getAttribute();
        void setAttribute(NODE_TYPE attr);
        Node(NODE_TYPE attribute);
        bool operator<(const Node<NODE_TYPE, EDGE_TYPE> &other) const;
        bool operator==(const Node<NODE_TYPE, EDGE_TYPE> &other) const;
        bool operator>(const Node<NODE_TYPE, EDGE_TYPE> &other) const;

};


template <class NODE_TYPE, class EDGE_TYPE>
Node<NODE_TYPE, EDGE_TYPE>::Node(NODE_TYPE attribute):attribute(attribute){
}

template <class NODE_TYPE, class EDGE_TYPE>
NODE_TYPE Node<NODE_TYPE, EDGE_TYPE>::getAttribute(){
    return this->attribute;
}

template <class NODE_TYPE, class EDGE_TYPE>
void Node<NODE_TYPE, EDGE_TYPE>::setAttribute(NODE_TYPE attr){
    this->attribute = attr;
}

template <class NODE_TYPE, class EDGE_TYPE>
bool Node<NODE_TYPE, EDGE_TYPE>::operator<(const Node<NODE_TYPE, EDGE_TYPE> &other) const{
    return this->attribute < other.attribute;
}

template <class NODE_TYPE, class EDGE_TYPE>
bool Node<NODE_TYPE, EDGE_TYPE>::operator==(const Node<NODE_TYPE, EDGE_TYPE> &other) const{
    return !((this->attribute < other.attribute) || (other.attribute < this->attribute ));
}

template <class NODE_TYPE, class EDGE_TYPE>
bool Node<NODE_TYPE, EDGE_TYPE>::operator>(const Node<NODE_TYPE, EDGE_TYPE> &other) const{
    return other.attribute < this->attribute;
}





#endif
