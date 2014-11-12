#include "LabelsValidationExperiment.hpp"
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <QList>
#include <time.h>
LabelsValidationExperiment::LabelsValidationExperiment():reader("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial/")
{
}

void LabelsValidationExperiment::run(){
    QList<FeatureFactoryAbstract*> Factories;
    LabelFeatureFactory labelFactory;
    Factories.append(&labelFactory);
    cn.load("/tmp/Implementation-Build/bin/complex_network.cn", Factories);
    qsrand(time(NULL));
    LabelGuesser l(&cn);
    int total=1;
    int acertos = 0;
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
