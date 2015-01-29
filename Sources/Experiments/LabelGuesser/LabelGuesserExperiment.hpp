#ifndef LABELGUESSEREXPERIMENT_HPP
#define LABELGUESSEREXPERIMENT_HPP

#include <QList>
class QString;
class SupervisedImage;
class FeaturesComplexNetwork;
class FeatureAbstract;
class IterativeRandomWalk;

using namespace std;
class LabelGuesserExperiment
{
private:
    QList<shared_ptr<FeatureAbstract> > getLabelsHints(SupervisedImage &img, unsigned int hide_idx );
    QList<QString> guessByIterativeRandomWalk(IterativeRandomWalk &walk, FeaturesComplexNetwork &cn,  QList<shared_ptr<FeatureAbstract> > hints);
    int getPosition(QList<QString>, QString);
    void printLabels(FeaturesComplexNetwork *cn);

public:
    LabelGuesserExperiment();



    void execute(QString, QString);



};

#endif // LABELGUESSEREXPERIMENT_HPP
