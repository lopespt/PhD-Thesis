#include <stdio.h>
#include <QApplication>
#include <Link.hpp>
#include <Feature.hpp>
#include <SunDatabaseReader.hpp>
#include <ComplexNetworkConstructor.hpp>
#include <AreaFeatureExtractor.hpp>
#include <locale>


int main(int argc, char **argv){

    
    QCoreApplication a(argc, argv);
    //QApplication a(argc, argv);
    setlocale(LC_ALL, "C");

    AreaFeatureExtractor feat;
    feat.setDiscretization(1000);
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
