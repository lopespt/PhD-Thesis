#include "Link.hpp"

Link::Link() : time(0), weight(0) {
}

Link::Link(link_time t, float weight, LinkType type) : time(t), weight(weight), type(type) {
}

float Link::getWeight() const {
    return this->weight;
}

void Link::setWeight(float weight) {
    this->weight = weight;
}

Link Link::operator+(float f) const {
    Link l(*this);
    l.weight += f;
    return l;
}


Link &Link::operator+=(float f) {
    this->weight += f;
    return *this;
}

link_time Link::getTime() const {
    return this->time;
}

void Link::setTime(link_time time) {
    this->time = time;
}


std::ostream &operator<<(std::ostream &os, const Link &dt) {
    os << dt.getWeight() << " " << dt.getTime() << " " << (int)dt.type;
    return os;
}

std::istream &operator>>(std::istream &is, Link &dt) {
    int i;
    is >> dt.weight >> dt.time >> i;
    dt.type = (Link::LinkType) i;
    return is;
}


Link::LinkType Link::getLinkType() const {
    return type;
}


void Link::setLinkType(Link::LinkType type) {
    this->type = type;
}
