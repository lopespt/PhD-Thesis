#include "LabelGuesserExperimentThread.hpp"
#include <QString>

LabelGuesserExperimentThread::LabelGuesserExperimentThread(float trainSize, int randomWalkSize, LabelGuesserExperiment::method method, QString inputFolder, QString outputFile):
    QThread(NULL),
    exp(trainSize, randomWalkSize, method),
    inputFolder(inputFolder),
    outputFile(outputFile)
{

}

void LabelGuesserExperimentThread::run(){
    exp.execute(inputFolder, outputFile);


}

LabelGuesserExperimentThread::~LabelGuesserExperimentThread()
{

}

