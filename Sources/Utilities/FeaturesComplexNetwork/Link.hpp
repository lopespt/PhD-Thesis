#ifndef LINK_HPP
#define LINK_HPP

#include <iostream>

typedef unsigned long long int link_time;

class Link {

protected:
    link_time time;
    float weight;

public:

    enum class LinkType{ OtherLabel, SameLabel } type;

    link_time getTime() const;

    void setTime(link_time time);

    float getWeight() const;

    void setWeight(float weight);

    Link();

    Link(link_time t, float weight, LinkType type);

    Link operator+(float) const;

    Link &operator+=(float);

    Link::LinkType getLinkType() const;

    void setLinkType(LinkType type);

    friend std::ostream &operator<<(std::ostream &os, const Link &dt);

    friend std::istream &operator>>(std::istream &os, Link &dt);

};

#endif
