#ifndef LABELGUESSEREXPERIMENT_HPP
#define LABELGUESSEREXPERIMENT_HPP

#include <QList>

class QString;
class SupervisedImage;
class FeaturesComplexNetwork;
class FeatureAbstractPtr;
class IterativeRandomWalk;


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
    QList<FeatureAbstractPtr > getLabelsHints(SupervisedImage &img, unsigned int hide_idx );
    QList<QString> guessByIterativeRandomWalk(IterativeRandomWalk &walk, FeaturesComplexNetwork &cn,  QList<FeatureAbstractPtr > hints);
    int getPosition(QList<QString>, QString);
    void printLabels(FeaturesComplexNetwork *cn);

    float trainPerc;
    int walkLenght;
    method m;

public:

    LabelGuesserExperiment(float trainPerc,int walkLenght, method m);



    void execute(QString, QString);



};

#endif // LABELGUESSEREXPERIMENT_HPP
