#include "LabelGuesserExperiment.hpp"

#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/IterativeRandomWalk.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/LabelFeature.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <QList>
#include <QString>
#include <stdio.h>
#include <Utilities/GraphUtilities.hpp>
#include <Utilities/ComplexNetworkConstructor/ReinforcementCoOcurrenceEquation.hpp>
#include <Utilities/DatabaseReader/DatabaseReader.hpp>
#include <Utilities/DatabaseReader/RegionChooser.hpp>
#include <time.h>

LabelGuesserExperiment::LabelGuesserExperiment(FeaturesComplexNetwork cn, QList<const FeatureFactoryAbstract*> factories ,  RegionChooser chooser , int walkLenght, method m):
    cn(cn),
    factories(factories),
    chooser(chooser),
    walkLenght(walkLenght),
    m(m)
{

}

QList< FeatureAbstractPtr > LabelGuesserExperiment::getFeaturesHints(SupervisedImage &img, unsigned int hide_idx){
    QList< FeatureAbstractPtr > ret;
  //  char buffer[100];
    for(int i=0;i<img.getRegions().size();i++){
        for(const FeatureFactoryAbstract*& fact: factories){
            if(i != hide_idx){
                ret.append(fact->CreateFromRegion(&img.getRegions()[i]));
    //            printf("dica: %s\n",ret.last()->asString(buffer));
            }
        }
    }
    return ret;
}

QList<QString> LabelGuesserExperiment::guessByIterativeRandomWalk(IterativeRandomWalk &walk, const QList<FeatureAbstractPtr >& hints){
    setlocale(LC_ALL, "en_US");
    char buffer[100];

    QList<FeaturesComplexNetwork::Node> ids;
    for(const FeatureAbstractPtr &s: hints){
        FeaturesComplexNetwork::Node id = cn.getNodeFromFeature(s);
        if( cn.valid(id))
            ids.append(id);
    }

    FeaturesComplexNetwork::NodeMap<double> final(cn);
    switch(m){
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


    foreach(FeaturesComplexNetwork::Node id, ids){
        walk.Execute(id, walkLenght);
        FeaturesComplexNetwork::NodeMap<double> probs(cn);
        walk.getAllProbs(probs);
        for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it){
            switch(m){
            case XorProbabilities:
                final[it] = final[it]  *(1 - probs[it]);
                break;
            case MultProbabilities:
                final[it] = final[it]  * probs[it];
                break;
            case SumProbabilities:
                final[it] = final[it] + probs[it];
                break;
            }

        }
    }

    QVector<FeaturesComplexNetwork::Node> order;
    for(FeaturesComplexNetwork::NodeIt i(cn); i != INVALID;++i){
        if(m==XorProbabilities)
            final[i] = 1 - final[i];
        order.append(i);
    }

    qSort(order.begin(), order.end(), [&](const FeaturesComplexNetwork::Node &a, const FeaturesComplexNetwork::Node &b){
        return final[b] < final[a];
    });

    QList<QString> retorno;
    for(int i=0;i<order.size();i++){
        FeatureAbstractPtr feat = cn.getNode(order[i]);
        if(feat.get()->getType() == 0)
            retorno.append( feat.get()->asString(buffer) );
    }

    return  retorno;
}

int LabelGuesserExperiment::getPosition(QList<QString> list, QString item){
    return list.indexOf(item);
}

void LabelGuesserExperiment::printLabels(FeaturesComplexNetwork *cn){
    char buffer[100];
    printf("S = {};\n");
    for(auto n = FeaturesComplexNetwork::NodeIt(*cn); n!= INVALID; ++n){
        printf("S(%d) = {'%s'};\n", cn->id(n), cn->getNode(n)->asString(buffer));
    }
}

void LabelGuesserExperiment::execute(QString outputFile){
    srand(time(0));

    cn.refreshCache();

    ListDigraph::ArcMap<double> weights(cn);
    GraphUtilities::getWeights(cn, weights);
    IterativeRandomWalk walk(cn, weights);

    FILE* file = fopen(outputFile.toStdString().c_str(), "w");
    assert( file );
    
    fprintf(file, "posicaoRankCorreto \t Escondido \t Top10Escolhidos \n");
    int position = 1;
    while(chooser.hasNextChoseRegion()){
        printf("%d (%d) ", position, chooser.getTotal());
        fflush(stdout);
        RegionChooser::ChosenRegion region = chooser.nextChoseRegion();
        SupervisedImage img = region.readSupervisedImage();

        const QList< FeatureAbstractPtr >& hints = getFeaturesHints(img, region.regionChoosed);
        QList<QString> guessed = guessByIterativeRandomWalk(walk, hints);
        QString hidden = img.getRegions()[region.regionChoosed].getLabel();


        fprintf(file, "%d", getPosition(guessed, hidden));
        fprintf(file, "\t\"%s\"\t", hidden.toStdString().c_str());
        for(int i=0;i<10;i++){
            fprintf(file, "\"%s\", ", guessed[i].toStdString().c_str());
        }
        fprintf(file,"\n");

        printf("%-3d %-20s %-20s\n", getPosition(guessed, hidden), hidden.toStdString().c_str(), guessed.first().toStdString().c_str() );
        fflush(file);
        position++;
    }
    fclose(file);
}
