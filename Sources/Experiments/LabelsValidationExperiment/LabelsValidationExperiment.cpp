#include "LabelsValidationExperiment.hpp"
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <QList>
#include <time.h>
LabelsValidationExperiment::LabelsValidationExperiment(QString sunDatabaseFolder, QString complexNetworkFile):sunDatabaseFolder(sunDatabaseFolder), complexNetworkFile(complexNetworkFile)
{
}

void LabelsValidationExperiment::run(){
    QList<FeatureFactoryAbstract*> Factories;
    LabelFeatureFactory labelFactory;
    OrientationFeatureFactory featureFactory(800);
    Factories.append(&labelFactory);
    Factories.append(&featureFactory);
    //for(int teste=0;teste<50;teste++){
        FeaturesComplexNetwork cn;
        cn.load(complexNetworkFile.toStdString().c_str(), Factories);
        qsrand(time(NULL));
        LabelGuesser l(&cn);

        int total=1;
        int acertos = 0;
        SunDatabaseReader reader(sunDatabaseFolder);
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
                printf("Acertos: %d | Analisadas: %d | Total: %d | %.0f%%\r", acertos, total, reader.getTotal() , acertos*100./total);
            }
        }
        printf("\n");
        fflush(stdout);
    //}

}
