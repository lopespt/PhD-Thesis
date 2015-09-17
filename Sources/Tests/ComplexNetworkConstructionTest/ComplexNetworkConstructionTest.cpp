#include <stdio.h>
#include <QApplication>
#include <FeatureExtractors/Feature.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <FeatureExtractors/LabelFeature.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>


int main(int argc, char **argv) {


    QCoreApplication a(argc, argv);
    //QApplication a(argc, argv);
    setlocale(LC_ALL, "");

    LabelFeatureFactory feat;
    AreaFeatureFactory area(10);
    QList<const FeatureFactoryAbstract *> extractors;
    extractors.append(&feat);
    extractors.append(&area);

    FeaturesComplexNetwork cn;
    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial");
    ComplexNetworkConstructor constructor(cn, r, extractors);
    constructor.build();

    FeaturesComplexNetwork::NodeIt it(cn);
    char buffer[50];
    char buffer2[50];
    for (; it != INVALID; ++it) {
        printf("%s\n", cn.getNode(it)->asString(buffer));
    }

    for (it = FeaturesComplexNetwork::NodeIt(cn); it != INVALID; ++it) {
        for (FeaturesComplexNetwork::OutArcIt j(cn, it); j != INVALID; ++j) {
            printf("%s -> %s: %f\n", cn.getNode(cn.source(j))->asString(buffer),
                   cn.getNode(cn.target(j))->asString(buffer2), cn.getLinkArcValue(j).getWeight());
        }
//        printf("%s\n", cn.getNode(it)->asString(buffer));
    }
    printf("nodes = %u\n", cn.getNumNodes());
    printf("edges = %u\n", cn.getNumArcs());
    cn.save("complex_network_save.cn");

    FeaturesComplexNetwork cn2;
    cn2.load("complex_network_save.cn", extractors);


    cn.clear();

    printf("nodes = %u\n", cn.getNumNodes());
    printf("edges = %u\n", cn.getNumArcs());
    //cn.load("complex_network_save.cn", extractors);
    printf("nodes = %u\n", cn.getNumNodes());
    printf("edges = %u\n", cn.getNumArcs());


    fflush(stdout);

    return 0;
}
