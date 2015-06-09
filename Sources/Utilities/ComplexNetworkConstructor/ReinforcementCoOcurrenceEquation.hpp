#ifndef REINFORCEMENTCOOCURRENCEEQUATION_HPP
#define REINFORCEMENTCOOCURRENCEEQUATION_HPP

#include "CoOcurrenceEquation.hpp"

class ReinforcementCoOcurrenceEquation : public CoOcurrenceEquation {
private:
    unsigned long long int time;

    /** Esta é a taxa de aprendizagem \f$ \alpha  \f$ */
    float learningRate;
    /** Esta é a influência do tempo na aprendizagem \f$ \lambda  \f$ */
    float lambda;
    float ma = 1; //Max weight
    float mi = 0.01; //Min weight
    float strength(float lastTimeOccurrence);

public:
    void reWeight(Link &l);

    void firstWeight(Link &l);

    ReinforcementCoOcurrenceEquation(float learningRate = 0.3, float lambda = 80);

    ~ReinforcementCoOcurrenceEquation();
};

#endif // REINFORCEMENTCOOCURRENCEEQUATION_HPP
