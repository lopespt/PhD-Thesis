#include <stdio.h>
#include <QApplication>
#include <FeatureExtractors/Feature.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/AreaFeatureExtractor.hpp>
#include <locale>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <Utilities/FeaturesComplexNetwork.hpp>

int main(int argc, char **argv){

    
    QCoreApplication a(argc, argv);
    //QApplication a(argc, argv);
    setlocale(LC_ALL, "");

    int discretization=10;
    AreaFeatureExtractor feat(discretization);
    QList<FeatureExtractorAbstract*> extractors;
    extractors.append(&feat);

    FeaturesComplexNetwork cn;
    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/Sun1/");
    ComplexNetworkConstructor constructor(cn, r, extractors);
    constructor.build();


    ComplexNetwork<const FeatureAbstract*, Link>::NodeIterator i = cn.Begin();
    char buffer[50];
    for(i=cn.Begin(); i!=cn.End();i++){
        printf("%s\n",(*i)->asString(buffer));
    }
    

    cn.save("complex_network_save.cn");


    fflush(stdout);

    return 0;
}
