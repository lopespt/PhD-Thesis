#ifndef COOCURRENCEEQUATION_HPP
#define COOCURRENCEEQUATION_HPP

class Link;

class Region;

class CoOcurrenceEquation {
public:
    virtual void reWeight(Link &l) = 0;

    virtual void firstWeight(Link &l) = 0;

    virtual ~CoOcurrenceEquation();
};

#endif // COOCURRENCEEQUATION_HPP
