#include <stdio.h>
#include <QApplication>
#include <FeatureExtractors/Feature.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/AreaFeatureExtractor.hpp>
#include <locale>

int main(int argc, char **argv){

    
    QCoreApplication a(argc, argv);
    //QApplication a(argc, argv);
    setlocale(LC_ALL, "C");

    AreaFeatureExtractor feat;
    feat.setDiscretization(10);
    QList<FeatureExtractor*> extractors;
    extractors.append(&feat);


    ComplexNetwork<Feature, Link> cn;
    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial/");
    ComplexNetworkConstructor constructor(cn, r, extractors);
    constructor.build();
    

    cn.save("complex_network_save.cn");


    fflush(stdout);

    return 0;
}
