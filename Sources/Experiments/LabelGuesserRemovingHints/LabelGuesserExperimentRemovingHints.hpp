#ifndef LABELGUESSEREXPERIMENTREMOVINGHINTS_HPP
#define LABELGUESSEREXPERIMENTREMOVINGHINTS_HPP

#include <QList>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
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

class LabelGuesserExperimentRemovingHints {
public:
    typedef enum {
        MultProbabilities,
        SumProbabilities,
        XorProbabilities
    } method;

private:
    std::mutex mtx;
    QList<FeatureAbstractPtr> getFeaturesHints(SupervisedImage &img, unsigned int hide_idx);
    QList<FeatureAbstractPtr> getLocalFeaturesHints(SupervisedImage &img, unsigned int hide_idx);

    QList<QString> guessByIterativeRandomWalk(IterativeRandomWalk &walk, const QList<FeatureAbstractPtr> &hints);
    QList<QString> guessByIterativeRandomWalkWithLocalFeatures(IterativeRandomWalk &walk, const QList<FeatureAbstractPtr> &hints, const QList<FeatureAbstractPtr> &localFeatures);
    float evaluateLocalFeatures(const FeaturesComplexNetwork::Node& node, const QList<FeatureAbstractPtr> &localFeatures);

    int getPosition(QList<QString>, QString);

    void printLabels(FeaturesComplexNetwork *cn);

    FeaturesComplexNetwork cn;
    QList<const FeatureFactoryAbstract *> factories;
    RegionChooser &chooser;
    int walkLenght;
    method m;
    int threads;
    float useLabels;
    int position;
    FILE *file;
public:

    LabelGuesserExperimentRemovingHints(FeaturesComplexNetwork cn, QList<const FeatureFactoryAbstract *> factories,
                           RegionChooser &chooser, int walkLenght, method m, int threads, float percentLabelsHintsUsed = 1.0);


    void execute(QString);

    class execTask: public QRunnable{
    private:
        LabelGuesserExperimentRemovingHints &exp;
        IterativeRandomWalk walk;
    public:

        execTask(LabelGuesserExperimentRemovingHints &exp, ListDigraph::ArcMap <double> &weights) : exp(exp), walk(exp.cn, weights) { setAutoDelete(true); }

        virtual void run() override;
    };


    //friend class LabelGuesserExperiment::execTask;

};

#endif // LABELGUESSEREXPERIMENTREMOVINGHINTS_HPP
