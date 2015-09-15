#include "ReinforcementCoOcurrenceEquation.hpp"
#include <Utilities/FeaturesComplexNetwork/Link.hpp>
#include <math.h>

ReinforcementCoOcurrenceEquation::ReinforcementCoOcurrenceEquation(float learningRate, float lambda) : time(1),
                                                                                                       learningRate(
                                                                                                               learningRate),
                                                                                                       lambda(lambda) {

}

float ReinforcementCoOcurrenceEquation::strength(float delta_t) {
    return (ma - mi) * pow(2, (1 - delta_t) / (lambda - 1)) + mi;
}

void ReinforcementCoOcurrenceEquation::reWeight(Link &l) {
    float delta_t = this->time - l.getTime();
    l.setTime(this->time);
    double weight = l.getWeight();
    weight = weight + learningRate * (strength(delta_t) - weight);
    //printf("delta_t = %f\tfinal: %f  \n",delta_t, weight);
    //fflush(stdout);
    l.setWeight(weight);
    this->time++;
}

void  ReinforcementCoOcurrenceEquation::firstWeight(Link &l) {
    l.setTime(time++);
    l.setWeight(mi);
}

ReinforcementCoOcurrenceEquation::~ReinforcementCoOcurrenceEquation() {

}

