//
// Created by Guilherme Wachs on 15/09/15.
//

#ifndef PHDTHESIS_SAMEOBJECTLINK_HPP
#define PHDTHESIS_SAMEOBJECTLINK_HPP

#include "Link.hpp"

class SameObjectLink : public Link {
public:
    SameObjectLink() : Link(){
        setLinkType(LinkType::SameLabel);
    }
    SameObjectLink(link_time time, float weight) : Link(time, weight, LinkType::SameLabel ){ }

};


#endif //PHDTHESIS_SAMEOBJECTLINK_HPP
