#include <stdio.h>
#include <QApplication>
#include <FeatureExtractors/Feature.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <locale>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <Utilities/FeaturesComplexNetwork.hpp>
#include <FeatureExtractors/LabelFeature.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>

int main(int argc, char **argv){

    
    QCoreApplication a(argc, argv);
    //QApplication a(argc, argv);
    setlocale(LC_ALL, "");

    int discretization=10;
    LabelFeatureFactory feat;
    QList<FeatureFactoryAbstract*> extractors;
    extractors.append(&feat);

    FeaturesComplexNetwork cn;
    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/Sun1/");
    ComplexNetworkConstructor constructor(cn, r, extractors);
    constructor.build();

    FeaturesComplexNetwork::NodeIterator i = cn.Begin();
    char buffer[50];
    for(i=cn.Begin(); i!=cn.End();i++){
        printf("%s\n",(*i)->asString(buffer));
    }
    
    for(i=cn.Begin(); i!=cn.End();i++){
        for(FeaturesComplexNetwork::EdgeIterator j = cn.EdgesBegin(i.getNodeId()); j != cn.EdgesEnd(i.getNodeId()); j++){
            printf("peso: %f\n", j->getWeight());
        }
        printf("%s\n",(*i)->asString(buffer));
    }
    printf("nodes = %u\n", cn.getNumNodes());
    printf("edges = %u\n", cn.getNumEdges());
    cn.save("complex_network_save.cn");
    cn.clear();

    printf("nodes = %u\n", cn.getNumNodes());
    printf("edges = %u\n", cn.getNumEdges());
    cn.load("complex_network_save.cn", extractors);
    printf("nodes = %u\n", cn.getNumNodes());
    printf("edges = %u\n", cn.getNumEdges());


    fflush(stdout);

    return 0;
}
