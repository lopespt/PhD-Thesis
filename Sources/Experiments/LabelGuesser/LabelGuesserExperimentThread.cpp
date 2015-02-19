#include "LabelGuesserExperimentThread.hpp"
#include <QString>

LabelGuesserExperimentThread::LabelGuesserExperimentThread( FeaturesComplexNetwork cn, RegionChooser chooser , int randomWalkSize, LabelGuesserExperiment::method method, QString inputFolder, QString outputFile):
    QThread(NULL),
    exp(cn, chooser, randomWalkSize, method),
    inputFolder(inputFolder),
    outputFile(outputFile)
{

}

void LabelGuesserExperimentThread::run(){
    exp.execute(outputFile);


}

LabelGuesserExperimentThread::~LabelGuesserExperimentThread()
{

}

