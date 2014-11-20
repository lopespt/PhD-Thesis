#include "LabelsValidationExperiment.hpp"
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <Utilities/KFoldDatabaseReader.hpp>
#include <QList>
#include <time.h>
#include <Utilities/ComplexNetworkConstructor.hpp>
LabelsValidationExperiment::LabelsValidationExperiment(QString sunDatabaseFolder, QString complexNetworkFile):sunDatabaseFolder(sunDatabaseFolder), complexNetworkFile(complexNetworkFile)
{
}
void LabelsValidationExperiment::buildComplexNetwork(DatabaseReader &reader){
    FeaturesComplexNetwork labels_cn;
    QList<FeatureFactoryAbstract*> factories;
    LabelFeatureFactory labels_factory;
    OrientationFeatureFactory orientation_factory(2000);
    factories.append(&labels_factory);
    factories.append(&orientation_factory);

    ComplexNetworkConstructor constructor(labels_cn,reader,factories);
    constructor.build();
    printf("%u\n", labels_cn.getNumNodes());
    printf("%u", labels_cn.getNumEdges());


    labels_cn.save("complex_network_tmp.cn");

}

void LabelsValidationExperiment::run(){
    QList<FeatureFactoryAbstract*> Factories;
    LabelFeatureFactory labelFactory;
    OrientationFeatureFactory featureFactory(2000);
    Factories.append(&labelFactory);
    Factories.append(&featureFactory);

    QFile resultados("resultados.txt");
    resultados.open(QIODevice::WriteOnly | QIODevice::Text);

    for(int teste=0;teste<1;teste++){
        FeaturesComplexNetwork cn;
        cn.load(complexNetworkFile.toStdString().c_str(), Factories);
        qsrand(time(NULL));
        LabelGuesser l(&cn);

        int total=0;
        int acertos = 0;
        SunDatabaseReader reader(sunDatabaseFolder);
        //KFoldDatabaseReader kfold(reader, 0.75);
        //auto trainReader = kfold.getTrainReader();
        //auto testReader = kfold.getTestReader();

        while(reader.hasNext()){
            SupervisedImage img = reader.readNext();
            if(img.getRegions().size()>1){
                unsigned int idx = qrand()%img.getRegions().size();
                bool guessed = l.Guess(&img, idx) ;
                //if(guessed == img.getRegions().at(idx).getLabel()){
                if(guessed){
                    acertos++;
                };
                //printf("%s: \n", l.Guess(&img, qrand()%img.getRegions().size()) ? "Acertou": "Errou");
                total++;
                printf("Acertos: %d | Analisadas: %d | Total: %d | %.0f%%\r", acertos, total+1, reader.getTotal() , acertos*100./total);
                fflush(stdout);
            }
        }
        resultados.write(QString("%1\t%2\t%3\n").arg(acertos).arg(total+1).arg(acertos*100./total).toLocal8Bit());
        resultados.flush();

        printf("\n");
        fflush(stdout);
    }
    resultados.close();

}
