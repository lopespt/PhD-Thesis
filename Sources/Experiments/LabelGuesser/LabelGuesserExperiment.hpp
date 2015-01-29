#ifndef LABELGUESSEREXPERIMENT_HPP
#define LABELGUESSEREXPERIMENT_HPP

#include <QList>
class QString;
class SupervisedImage;
class FeaturesComplexNetwork;
class FeatureAbstract;
class IterativeRandomWalk;
class LabelGuesserExperiment

{
private:
    QList<FeatureAbstract *> getLabelsHints(SupervisedImage &img, unsigned int hide_idx );
    QList<QString> guessByIterativeRandomWalk(IterativeRandomWalk &walk, FeaturesComplexNetwork &cn,  QList<FeatureAbstract*> hints);
    int getPosition(QList<QString>, QString);
    void printLabels(FeaturesComplexNetwork *cn);

public:
    LabelGuesserExperiment();



    void execute(QString, QString);



};

#endif // LABELGUESSEREXPERIMENT_HPP
