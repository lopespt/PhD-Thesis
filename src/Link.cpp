
#include "Link.hpp"

Link::Link():time(0), weight(0){
}

Link::Link(link_time t, float weight):time(t), weight(weight){
}

float Link::getWeight() const{
    return this->weight;
}

void Link::setWeight(float weight){
    this->weight = weight;
}

Link Link::operator+(float f) const{
    Link l(*this);
    l.weight += f;
    return l;
}


Link& Link::operator+=(float f){
    this->weight+=f;
    return *this;
}

link_time Link::getTime() const{
    return this->time;
}

void Link::setTime(link_time time){
    this->time = time;
}

