#include "LabelGuesserExperimentThread.hpp"

LabelGuesserExperimentThread::LabelGuesserExperimentThread(FeaturesComplexNetwork cn,
                                                           QList<const FeatureFactoryAbstract *> factories,
                                                           RegionChooser chooser, int randomWalkSize,
                                                           LabelGuesserExperiment::method method, QString inputFolder,
                                                           QString outputFile) :
        QThread(NULL),
        exp(cn, factories, chooser, randomWalkSize, method),
        inputFolder(inputFolder),
        outputFile(outputFile) {

}

void LabelGuesserExperimentThread::run() {
    exp.execute(outputFile);


}

LabelGuesserExperimentThread::~LabelGuesserExperimentThread() {

}

