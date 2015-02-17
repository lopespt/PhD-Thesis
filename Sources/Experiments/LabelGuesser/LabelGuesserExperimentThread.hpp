#ifndef LABELGUESSEREXPERIMENTTHREAD_HPP
#define LABELGUESSEREXPERIMENTTHREAD_HPP

#include <QThread>
#include "LabelGuesserExperiment.hpp"
class QString;

class LabelGuesserExperimentThread: public QThread
{
    Q_OBJECT
private:
    LabelGuesserExperiment exp;
    QString inputFolder;
    QString outputFile;
public:
    LabelGuesserExperimentThread(float trainSize, int randomWalkSize, LabelGuesserExperiment::method method, QString inputFolder, QString outputFile );
    void run();
    ~LabelGuesserExperimentThread();

};

#endif // LABELGUESSEREXPERIMENTTHREAD_HPP
