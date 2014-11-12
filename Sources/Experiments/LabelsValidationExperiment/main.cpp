#include <QCoreApplication>
#include "LabelsValidationExperiment.hpp"

int main(int argc, char* argv[]){
    QCoreApplication app(argc, argv);

    LabelsValidationExperiment experiment;
    experiment.run();

    return 0;
}
