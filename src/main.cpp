#include <stdio.h>
#include <QApplication>
#include "SunDatabaseReader.hpp"
#include "ComplexNetworkConstructor.hpp"
#include "AreaFeatureExtractor.hpp"
#include <locale>

int main(int argc, char **argv){

    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);
    setlocale(LC_ALL, "C");
    AreaFeatureExtractor feat;
    feat.setDiscretization(32);
    QList<FeatureExtractor*> extractors;
    extractors.append(&feat);

    ComplexNetwork<Feature, float> cn;
    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial/");
    ComplexNetworkConstructor constructor(cn, r, extractors);
    constructor.analyseNext();

    return a.exec();
}
