#include <stdio.h>
#include <QApplication>
#include "ComplexNetwork.hpp"
#include "tests/ComplexNetworkTest.cpp"
#include "SunDatabaseReader.hpp"
#include "AreaFeature.hpp"
#include <locale>

int main(int argc, char **argv){

    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);
    setlocale(LC_ALL, "C");

    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial/");
    SupervisedImage* s=r.readNext();
    s=r.readNext();
    foreach(Region *rr, s->getRegions()){
        AreaFeature feat(rr);
        feat.extractFeature();
        feat.printFeature();
        fflush(stdout);
    }
    //}
    //initTest( 50000 , 50000000 );

    return a.exec();
}
