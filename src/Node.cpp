
#include "Node.hpp"

template <class ATTR_TYPE>
ATTR_TYPE Node<ATTR_TYPE>::getAttribute(){
    return this->attribute;
}

template <class ATTR_TYPE>
void Node<ATTR_TYPE>::setAttribute(ATTR_TYPE attr){
    this->attribute = attr;
}





