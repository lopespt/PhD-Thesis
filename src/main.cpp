#include <stdio.h>
#include <QCoreApplication>
#include <QApplication>
#include "ComplexNetwork.hpp"
#include "tests/ComplexNetworkTest.cpp"
#include "SunDatabaseReader.hpp"
#include <QFile>

int main(int argc, char **argv){

    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial/");
    SupervisedImage* s=r.readNext();
    //while((s=r.readNext())!=NULL){
    s->show_image();
        
    //}
    //initTest( 50000 , 50000000 );

    return a.exec();
}
