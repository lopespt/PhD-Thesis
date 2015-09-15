#include "LabelGuesserExperimentRemovingHints.hpp"
#include <Utilities/IterativeRandomWalk.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <Utilities/GraphUtilities.hpp>
#include <Utilities/ComplexNetworkConstructor/ReinforcementCoOcurrenceEquation.hpp>
#include <qthreadpool.h>

LabelGuesserExperimentRemovingHints::LabelGuesserExperimentRemovingHints(FeaturesComplexNetwork cn,
                                               QList<const FeatureFactoryAbstract *> factories, RegionChooser &chooser,
                                               int walkLenght, method m, int threads, float percentLabels) :
        cn(cn),
        factories(factories),
        chooser(chooser),
        walkLenght(walkLenght),
        m(m),
        threads(threads),
        useLabels(percentLabels),
        position(1),
        file(NULL)
{

}


QList<FeatureAbstractPtr> LabelGuesserExperimentRemovingHints::getLocalFeaturesHints(SupervisedImage &img, unsigned int hide_idx) {
    QList<FeatureAbstractPtr> ret;
    //  char buffer[100];

    for (const FeatureFactoryAbstract *&fact: factories) {
        if (fact->getType() != 0) {
            ret.append(fact->CreateFromRegion(&img.getRegions()[hide_idx]));
            //            printf("dica: %s\n",ret.last()->asString(buffer));
        }
    }

    return ret;
}


QList<FeatureAbstractPtr> LabelGuesserExperimentRemovingHints::getFeaturesHints(SupervisedImage &img, unsigned int hide_idx) {
    QList<FeatureAbstractPtr> ret;
    //  char buffer[100];
    for (int i = 0; i < img.getRegions().size(); i++) {
        for (const FeatureFactoryAbstract *&fact: factories) {
            if (i != hide_idx) {
            //if (i != hide_idx && (fact->getType() != 0)) {
                ret.append(fact->CreateFromRegion(&img.getRegions()[i]));
                //            printf("dica: %s\n",ret.last()->asString(buffer));
            }
        }
    }

    int totalHints = ret.size();
    //Retirando alguns hints...
    for(int i=0; i < totalHints * (1.0-useLabels); i++){
        ret.removeAt(rand() % ret.size());
    }

    return ret;
}


float LabelGuesserExperimentRemovingHints::evaluateLocalFeatures(const FeaturesComplexNetwork::Node& node, const QList<FeatureAbstractPtr> &localFeatures){

    float total = 0;
    for( FeaturesComplexNetwork::OutArcIt it(cn,node); it != INVALID; ++it ){
        if( cn.getArcValue(it).isSameLabel() && localFeatures.contains( cn.getNode( cn.target( it ) ) ) ) {
            total += cn.getArcValue(it).getWeight();
        }
    }
    for( FeaturesComplexNetwork::InArcIt it(cn,node); it != INVALID; ++it ){
        if( cn.getArcValue(it).isSameLabel() && localFeatures.contains( cn.getNode( cn.source( it ) ) ) ) {
            total += cn.getArcValue(it).getWeight();
        }
    }
    return total/localFeatures.size();
}

QList<QString> LabelGuesserExperimentRemovingHints::guessByIterativeRandomWalkWithLocalFeatures(
        IterativeRandomWalk &walk, const QList<FeatureAbstractPtr> &hints, const QList<FeatureAbstractPtr> &localFeatures) {

    setlocale(LC_ALL, "en_US");
    char buffer[100];

    QList<FeaturesComplexNetwork::Node> ids;
    for (const FeatureAbstractPtr &s: hints) {
        FeaturesComplexNetwork::Node id = cn.getNodeFromFeature(s);
        if (cn.valid(id))
            ids.append(id);
    }

    FeaturesComplexNetwork::NodeMap <double> final(cn);
    switch (m) {
        case XorProbabilities:
            GraphUtilities::fillMap(cn, final, 1.0);
            break;
        case MultProbabilities:
            GraphUtilities::fillMap(cn, final, 1.0);
            break;
        case SumProbabilities:
            GraphUtilities::fillMap(cn, final, 0.0);
            break;
    }


            foreach(FeaturesComplexNetwork::Node
                            id, ids) {
            walk.Execute(id, (unsigned int) walkLenght);
            FeaturesComplexNetwork::NodeMap <double> probs(cn);
            walk.getAllProbs(probs);
            for (FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it) {
                switch (m) {
                    case XorProbabilities:
                        final[it] = final[it] * (1 - probs[it]);
                        break;
                    case MultProbabilities:
                        final[it] = final[it] * probs[it];
                        break;
                    case SumProbabilities:
                        final[it] = final[it] + probs[it];
                        break;
                }

            }
        }


    QVector<FeaturesComplexNetwork::Node> order;
    for (FeaturesComplexNetwork::NodeIt i(cn); i != INVALID; ++i) {
        if (m == XorProbabilities)
            final[i] = 1 - final[i];
        order.append(i);
    }


    FeaturesComplexNetwork::NodeMap <double> localFeaturesGrade(cn);
    for (FeaturesComplexNetwork::NodeIt i(cn); i != INVALID; ++i) {
        localFeaturesGrade[i] = evaluateLocalFeatures(i, localFeatures);
    }


    //Ordem decrescente
    qSort(order.begin(), order.end(),
          [&](const FeaturesComplexNetwork::Node &a, const FeaturesComplexNetwork::Node &b) {
              return (final[b] ) < (final[a] );
              //return (final[b]  + localFeaturesGrade[b] ) < (final[a] + localFeaturesGrade[a] );
              //return ( localFeaturesGrade[b] ) < ( localFeaturesGrade[a] );
          });


    QList<QString> retorno;
    for (int i = 0; i < order.size(); i++) {
        FeatureAbstractPtr feat = cn.getNode(order[i]);
        if (feat.get()->getType() == 0 && evaluateLocalFeatures(order[i], localFeatures) > 0)
            retorno.append(feat.get()->asString(buffer));
    }

    return retorno;

}

QList<QString> LabelGuesserExperimentRemovingHints::guessByIterativeRandomWalk(IterativeRandomWalk &walk,
                                                                  const QList<FeatureAbstractPtr> &hints) {
    setlocale(LC_ALL, "en_US");
    char buffer[100];

    QList<FeaturesComplexNetwork::Node> ids;
    for (const FeatureAbstractPtr &s: hints) {
        FeaturesComplexNetwork::Node id = cn.getNodeFromFeature(s);
        if (cn.valid(id))
            ids.append(id);
    }

    FeaturesComplexNetwork::NodeMap <double> final(cn);
    switch (m) {
        case XorProbabilities:
            GraphUtilities::fillMap(cn, final, 1.0);
            break;
        case MultProbabilities:
            GraphUtilities::fillMap(cn, final, 1.0);
            break;
        case SumProbabilities:
            GraphUtilities::fillMap(cn, final, 0.0);
            break;
    }


            foreach(FeaturesComplexNetwork::Node
                            id, ids) {
            walk.Execute(id, (unsigned int) walkLenght);
            FeaturesComplexNetwork::NodeMap <double> probs(cn);
            walk.getAllProbs(probs);
            for (FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it) {
                switch (m) {
                    case XorProbabilities:
                        final[it] = final[it] * (1 - probs[it]);
                        break;
                    case MultProbabilities:
                        final[it] = final[it] * probs[it];
                        break;
                    case SumProbabilities:
                        final[it] = final[it] + probs[it];
                        break;
                }

            }
        }

    QVector<FeaturesComplexNetwork::Node> order;
    for (FeaturesComplexNetwork::NodeIt i(cn); i != INVALID; ++i) {
        if (m == XorProbabilities)
            final[i] = 1 - final[i];
        order.append(i);
    }

    qSort(order.begin(), order.end(),
          [&](const FeaturesComplexNetwork::Node &a, const FeaturesComplexNetwork::Node &b) {
              return final[b] < final[a];
          });



    QList<QString> retorno;
    for (int i = 0; i < order.size(); i++) {
        FeatureAbstractPtr feat = cn.getNode(order[i]);
        if (feat.get()->getType() == 0 )
            retorno.append(feat.get()->asString(buffer));
    }

    return retorno;
}

int LabelGuesserExperimentRemovingHints::getPosition(QList<QString> list, QString item) {
    return list.indexOf(item);
}

void LabelGuesserExperimentRemovingHints::printLabels(FeaturesComplexNetwork *cn) {
    char buffer[100];
    printf("S = {};\n");
    for (auto n = FeaturesComplexNetwork::NodeIt(*cn); n != INVALID; ++n) {
        printf("S(%d) = {'%s'};\n", cn->id(n), cn->getNode(n)->asString(buffer));
    }
}

void LabelGuesserExperimentRemovingHints::execute(QString outputFile) {
    chooser.reset();
    srand((unsigned int) time(0));

    cn.refreshCache();

    ListDigraph::ArcMap <double> weights(cn);
    GraphUtilities::getWeights(cn, weights);
    IterativeRandomWalk walk(cn, weights);

    file = fopen(outputFile.toStdString().c_str(), "w");
    assert(file);

    fprintf(file, "posicaoRankCorreto \t Escondido \t Top10Escolhidos \n");
    QThreadPool p;
    for(int i=0; i<threads; i++){
        p.start(new execTask(*this, weights));
    }
    p.waitForDone();

    /*while (chooser.hasNextChoseRegion()) {
        printf("%d (%d) ", position, chooser.getTotal());
        fflush(stdout);
        RegionChooser::ChosenRegion region = chooser.nextChoseRegion();
        SupervisedImage img = region.readSupervisedImage();

        const QList<FeatureAbstractPtr> &hints = getFeaturesHints(img, region.regionChoosed);
        QList<QString> guessed = guessByIterativeRandomWalk(walk, hints);
        QString hidden = img.getRegions()[region.regionChoosed].getLabel();


        fprintf(file, "%d", getPosition(guessed, hidden));
        fprintf(file, "\t\"%s\"\t", hidden.toStdString().c_str());
        for (int i = 0; i < 10; i++) {
            fprintf(file, "\"%s\", ", guessed[i].toStdString().c_str());
        }
        fprintf(file, "\n");

        printf("%-3d %-20s %-20s\n", getPosition(guessed, hidden), hidden.toStdString().c_str(),
               guessed.first().toStdString().c_str());
        fflush(file);
        position++;
    }*/
    fclose(file);
}

void LabelGuesserExperimentRemovingHints::execTask::run() {
    while (true) {
        exp.mtx.lock();
        if(!exp.chooser.hasNextChoseRegion()) {
            exp.mtx.unlock();
            break;
        }

        int gp=exp.position;
        RegionChooser::ChosenRegion region = exp.chooser.nextChoseRegion();
        exp.position++;
        exp.mtx.unlock();


        SupervisedImage img = region.readSupervisedImage();
        const QList<FeatureAbstractPtr> &hints = exp.getFeaturesHints(img, region.regionChoosed);
        //QList<QString> guessed = exp.guessByIterativeRandomWalk(walk, hints);

        const QList<FeatureAbstractPtr> &localFeatures = exp.getLocalFeaturesHints(img, region.regionChoosed);
        QList<QString> guessed = exp.guessByIterativeRandomWalkWithLocalFeatures(walk, hints, localFeatures);


        QString hidden = img.getRegions()[region.regionChoosed].getLabel();


        exp.mtx.lock();
        printf("%d (%d) ", gp, exp.chooser.getTotal());
        fprintf(exp.file, "%d", exp.getPosition(guessed, hidden));
        fprintf(exp.file, "\t\"%s\"\t", hidden.toStdString().c_str());
        for (int i = 0; i < 10; i++) {
            fprintf(exp.file, "\"%s\", ", guessed[i].toStdString().c_str());
        }
        fprintf(exp.file, "\n");

        printf("%-3d %-20s %-20s\n", exp.getPosition(guessed, hidden), hidden.toStdString().c_str(),
               guessed.first().toStdString().c_str());
        fflush(exp.file);
        fflush(stdout);
        exp.mtx.unlock();
    }
}

