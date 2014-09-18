#include <stdio.h>
#include <QCoreApplication>
#include "ComplexNetwork.hpp"
#include "tests/ComplexNetworkTest.cpp"
#include "SunDatabaseReader.hpp"

int main(int argc, char **argv){

    QCoreApplication a(argc, argv);

    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial");
    
    //initTest( 50000 , 50000000 );

    return 0;
}
