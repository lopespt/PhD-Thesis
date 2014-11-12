#include "LabelsValidationExperiment.hpp"
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <QList>
#include <time.h>
LabelsValidationExperiment::LabelsValidationExperiment()
{
}

void LabelsValidationExperiment::run(){
    QList<FeatureFactoryAbstract*> Factories;
    LabelFeatureFactory labelFactory;
    Factories.append(&labelFactory);
    cn.load("/tmp/Implementation-Build/bin/complex_network.cn", Factories);
    for(int teste=0;teste<50;teste++){
    qsrand(time(NULL));
    LabelGuesser l(&cn);
    int total=1;
    int acertos = 0;
    SunDatabaseReader reader("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial/");
    while(reader.hasNext()){
        SupervisedImage img = reader.readNext();
        if(l.Guess(&img, qrand()%img.getRegions().size())){
            acertos++;
        };
       // printf("%s: \n", l.Guess(&img, qrand()%img.getRegions().size()) ? "Acertou": "Errou");
        total++;
    }
    printf("Acertos: %d | Total: %d | %f%%\n", acertos, total, acertos*100./total);
    }

}
