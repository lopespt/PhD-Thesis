#ifndef LABELSVALIDATIONEXPERIMENT_HPP
#define LABELSVALIDATIONEXPERIMENT_HPP

#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include "LabelGuesser.hpp"
class LabelsValidationExperiment
{
private:
    FeaturesComplexNetwork cn;
    QString sunDatabaseFolder, complexNetworkFile;

public:
    LabelsValidationExperiment(QString sunDatabaseFolder, QString complexNetworkFile);
    void run();
};

#endif // LABELSVALIDATIONEXPERIMENT_HPP
