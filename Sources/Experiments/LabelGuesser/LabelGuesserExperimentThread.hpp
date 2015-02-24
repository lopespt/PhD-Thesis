#ifndef LABELGUESSEREXPERIMENTTHREAD_HPP
#define LABELGUESSEREXPERIMENTTHREAD_HPP

#include <QThread>
#include <QObject>
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
    LabelGuesserExperimentThread(FeaturesComplexNetwork cn, QList<const FeatureFactoryAbstract*> factories, RegionChooser chooser,  int randomWalkSize, LabelGuesserExperiment::method method, QString inputFolder, QString outputFile );
    void run();
    ~LabelGuesserExperimentThread();

};

#endif // LABELGUESSEREXPERIMENTTHREAD_HPP
