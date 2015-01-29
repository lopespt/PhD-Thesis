#include "LabelGuesserExperiment.hpp"

#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/IterativeRandomWalk.hpp>
#include <Utilities/KFoldDatabaseReader.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <Utilities/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/LabelFeature.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <QList>
#include <QString>
#include <stdio.h>

LabelGuesserExperiment::LabelGuesserExperiment()
{
}

QList<FeatureAbstract*> LabelGuesserExperiment::getLabelsHints(SupervisedImage &img, unsigned int hide_idx){
    QList<FeatureAbstract *> ret;
    LabelFeatureFactory fact;
    //char buffer[100];
    for(int i=0;i<img.getRegions().size();i++){
        if(i != hide_idx){
            ret.append(fact.CreateFromRegion(&img.getRegions()[i]));
            //printf("dica: %s\n",ret.last()->asString(buffer));
        }
    }
    return ret;
}

QList<QString> LabelGuesserExperiment::guessByIterativeRandomWalk(IterativeRandomWalk &walk, FeaturesComplexNetwork &cn, QList<FeatureAbstract*> hints){
//    IterativeRandomWalk walk(&cn);
    setlocale(LC_ALL, "en_US");

    QList<node_id> ids;
    foreach(FeatureAbstract* s, hints){
        node_id id = cn.getNodeFromFeature(s);
        if(id != -1)
            ids.append(id);
        delete s;
    }

    QVector<double> final;
    final.resize(cn.getNumNodes());
    final.fill(1);

    foreach(node_id id, ids){
        walk.Execute(id, 2);
        QVector<double> probs = walk.getAllProbs();
        for(unsigned int i = 0; i<final.size();i++){
            final[i] = final[i] *  (probs[i]);
        }
        /*printf("n%d = [\n", id);
        for(unsigned int i = 0; i<final.size();i++){
            printf("%f\n", probs[i]);
        }
        printf("];\n");*/
    }

    QVector<node_id> order;
    for(unsigned int i = 0; i < final.size();i++){
        //final[i] = 1 - final[i];
        order.append(i);
    }

    qSort(order.begin(), order.end(), [&](const double &a, const double &b){return final[b] < final[a];});

    QList<QString> retorno;
    char buffer[100];
    for(int i=0;i<order.size();i++){
        //printf("%% %s: %e \n", cn.getNode(order[i])->get()->asString(buffer), final[order[i]]);
        retorno.append( cn.getNode(order[i])->get()->asString(buffer) );
    }

    return  retorno;
}

int LabelGuesserExperiment::getPosition(QList<QString> list, QString item){
    return list.indexOf(item);
}

void LabelGuesserExperiment::printLabels(FeaturesComplexNetwork *cn){
    char buffer[100];
    printf("S = {};\n");
    for(auto n=cn->Begin(); n!=cn->End();n++){
        printf("S(%d) = {'%s'};\n", n.getNodeId()+1, (*n)->asString(buffer));
    }
}

void LabelGuesserExperiment::execute(QString inputFolder, QString outputFile){
    srand(time(0));
    SunDatabaseReader r = SunDatabaseReader(inputFolder) ;
    KFoldDatabaseReader kfold(r, 0.7);
    KFoldDatabaseReader::PathDatabaseReader train = kfold.getTrainReader();
    KFoldDatabaseReader::PathDatabaseReader test = kfold.getTestReader();

    //Create network
    QList<FeatureFactoryAbstract*> factories;
    LabelFeatureFactory lblFactory;
    factories.append(&lblFactory);
    FeaturesComplexNetwork cn;
    ComplexNetworkConstructor constructor(cn, train, factories);
    constructor.build();
    cn.save("train.cn");
    //cn.load("/tmp/Implementation-Build/bin/labels.cn", factories);
    //cn.load("train.cn", factories);
    cn.updateIndex();
    IterativeRandomWalk walk(&cn);
    

    FILE* file = fopen(outputFile.toStdString().c_str(), "w");
    
    fprintf(file, "%%Escondido %%Top10Escolhidos %%posicaoEscolhido\n");
    //"%%Escondido %%Top10Escolhidos  %%posEscolhido\n";
    int position = 1;
    printf("teste");
    while(test.hasNext() && position < 10){
        printf("%d (%d) ", position, test.getTotal());
        fflush(stdout);
        SupervisedImage img = test.readNext();
        while(img.getRegions().size() < 2){
            img = test.readNext();
        }
        QList<Region> regs = img.getRegions();
        unsigned int choosen = rand() % regs.size();
        QList<FeatureAbstract*> hints = getLabelsHints(img, choosen);

        QList<QString> guessed = guessByIterativeRandomWalk(walk,cn, hints);
        QString hidden = img.getRegions()[choosen].getLabel();

        fprintf(file, "%s\t", hidden.toStdString().c_str());
        for(int i=0;i<10;i++){
          //  fprintf(file, "%s ", guessed[i].toStdString().c_str());
        }
        fprintf(file, "\t%d\n", getPosition(guessed, hidden));
        printf("%-3d %-20s %-20s\n", getPosition(guessed, hidden), hidden.toStdString().c_str(), guessed.first().toStdString().c_str() );
        fflush(file);
        position++;

    }
    fclose(file);
}
