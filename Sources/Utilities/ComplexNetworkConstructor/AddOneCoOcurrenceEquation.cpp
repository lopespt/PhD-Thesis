#include "AddOneCoOcurrenceEquation.hpp"
#include <Utilities/Link.hpp>

AddOneCoOcurrenceEquation::AddOneCoOcurrenceEquation() : time(1) {

}

void AddOneCoOcurrenceEquation::reWeight(Link &l) {
    l.setTime(++time);
    l.setWeight(l.getWeight() + 1);
}

void AddOneCoOcurrenceEquation::firstWeight(Link &l) {
    l.setTime(++time);
    l.setWeight(1);
}

AddOneCoOcurrenceEquation::~AddOneCoOcurrenceEquation() {

}

