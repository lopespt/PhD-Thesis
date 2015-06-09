#ifndef ADDONECOOCURRENCEEQUATION_HPP
#define ADDONECOOCURRENCEEQUATION_HPP

#include "CoOcurrenceEquation.hpp"

class AddOneCoOcurrenceEquation : public CoOcurrenceEquation {
private:
    unsigned long long int time;

public:
    inline void reWeight(Link &l);

    inline void firstWeight(Link &l);

    AddOneCoOcurrenceEquation();

    ~AddOneCoOcurrenceEquation();
};

#endif // ADDONECOOCURRENCEEQUATION_HPP
