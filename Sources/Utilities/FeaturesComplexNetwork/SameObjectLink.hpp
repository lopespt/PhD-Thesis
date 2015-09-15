//
// Created by Guilherme Wachs on 15/09/15.
//

#ifndef PHDTHESIS_SAMEOBJECTLINK_HPP
#define PHDTHESIS_SAMEOBJECTLINK_HPP

#include "Link.hpp"

class SameObjectLink : public Link {
public:
    SameObjectLink() : Link(), isSameLabel(true){ }
    SameObjectLink(link_time time, float weight) : Link(time, weight, true){ }

};


#endif //PHDTHESIS_SAMEOBJECTLINK_HPP
