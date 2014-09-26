#include <stdio.h>
#include <QApplication>
#include "Link.hpp"
#include "Feature.hpp"
#include "SunDatabaseReader.hpp"
#include "ComplexNetworkConstructor.hpp"
#include "AreaFeatureExtractor.hpp"
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
    
    /*ComplexNetwork<int, int> cn;
    cn.addNode(new Node<int, int>(2));
    cn.addNode(new Node<int, int>(20));
    cn.addNode(new Node<int, int>(22));
    cn.addNode(new Node<int, int>(23));
    cn.addNode(new Node<int, int>(24));
    */
    cn.save("teste");
    fflush(stdout);

        return 0;
    //return a.exec();
}
