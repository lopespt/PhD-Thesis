#include "AddOneCoOcurrenceEquation.hpp"
#include <Utilities/FeaturesComplexNetwork/Link.hpp>

AddOneCoOcurrenceEquation::AddOneCoOcurrenceEquation() : time(1) {

}

void AddOneCoOcurrenceEquation::reWeight(Link &l) {
    l.setTime(1);
    l.setWeight(l.getWeight() + 1);
}

void AddOneCoOcurrenceEquation::firstWeight(Link &l) {
    l.setTime(1);
    l.setWeight(1);
}

AddOneCoOcurrenceEquation::~AddOneCoOcurrenceEquation() {

}

