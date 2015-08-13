#ifndef LABELGUESSEREXPERIMENT_HPP
#define LABELGUESSEREXPERIMENT_HPP

#include <QList>
#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/DatabaseReader/RegionChooser.hpp>
#include <QtCore/qrunnable.h>
#include <mutex>
#include <Utilities/IterativeRandomWalk.hpp>

class QString;

class SupervisedImage;

class FeatureAbstractPtr;

class IterativeRandomWalk;

class FeatureFactoryAbstract;

class DatabaseReader;

class RegionChooser;


using namespace std;

class LabelGuesserExperiment {
public:
    typedef enum {
        MultProbabilities,
        SumProbabilities,
        XorProbabilities
    } method;

private:
    std::mutex mtx;
    QList<FeatureAbstractPtr> getFeaturesHints(SupervisedImage &img, unsigned int hide_idx);

    QList<QString> guessByIterativeRandomWalk(IterativeRandomWalk &walk, const QList<FeatureAbstractPtr> &hints);

    int getPosition(QList<QString>, QString);

    void printLabels(FeaturesComplexNetwork *cn);

    FeaturesComplexNetwork cn;
    QList<const FeatureFactoryAbstract *> factories;
    RegionChooser &chooser;
    int walkLenght;
    method m;
    int threads;
    bool useLabels;
    int position;
    FILE *file;
public:

    LabelGuesserExperiment(FeaturesComplexNetwork cn, QList<const FeatureFactoryAbstract *> factories,
                           RegionChooser &chooser, int walkLenght, method m, int threads, bool useLabels = true);


    void execute(QString);

    class execTask: public QRunnable{
    private:
        LabelGuesserExperiment &exp;
        IterativeRandomWalk walk;
    public:

        execTask(LabelGuesserExperiment &exp, ListDigraph::ArcMap <double> &weights) : exp(exp), walk(exp.cn, weights) { setAutoDelete(true); }

        virtual void run() override;
    };


    //friend class LabelGuesserExperiment::execTask;

};

#endif // LABELGUESSEREXPERIMENT_HPP
