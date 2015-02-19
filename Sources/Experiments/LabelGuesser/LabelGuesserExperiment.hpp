#ifndef LABELGUESSEREXPERIMENT_HPP
#define LABELGUESSEREXPERIMENT_HPP

#include <QList>
#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/DatabaseReader/RegionChooser.hpp>

class QString;
class SupervisedImage;
class FeatureAbstractPtr;
class IterativeRandomWalk;
class FeatureFactoryAbstract;
class DatabaseReader;
class RegionChooser;


using namespace std;

class LabelGuesserExperiment
{
public:
     typedef enum{
        MultProbabilities,
        SumProbabilities,
        XorProbabilities
    }method;

private:
    QList<FeatureAbstractPtr> getLabelsHints(SupervisedImage &img, unsigned int hide_idx );
    QList<QString> guessByIterativeRandomWalk(IterativeRandomWalk &walk, QList<FeatureAbstractPtr > hints);
    int getPosition(QList<QString>, QString);
    void printLabels(FeaturesComplexNetwork *cn);

    FeaturesComplexNetwork cn;
    RegionChooser chooser;
    int walkLenght;
    method m;

public:

    LabelGuesserExperiment(FeaturesComplexNetwork cn, RegionChooser chooser, int walkLenght, method m);



    void execute(QString);



};

#endif // LABELGUESSEREXPERIMENT_HPP
