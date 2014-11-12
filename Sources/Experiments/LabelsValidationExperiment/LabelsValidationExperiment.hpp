#ifndef LABELSVALIDATIONEXPERIMENT_HPP
#define LABELSVALIDATIONEXPERIMENT_HPP

#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include "LabelGuesser.hpp"
class LabelsValidationExperiment
{
private:
    FeaturesComplexNetwork cn;

public:
    LabelsValidationExperiment();
    void run();
};

#endif // LABELSVALIDATIONEXPERIMENT_HPP
