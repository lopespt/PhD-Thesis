

#ifndef NODE__H
#define NODE__H
template <class ATTR_TYPE>
class Node;
#include "Edge.hpp"

template <class ATTR_TYPE>
class Node{
    private:
        int _id;
        ATTR_TYPE attribute;
    public:
        ATTR_TYPE getAttribute();
        void setAttribute(ATTR_TYPE attr);
};


#endif
