#include <stdio.h>
#include <QCoreApplication>
#include "ComplexNetwork.hpp"
#include "tests/ComplexNetworkTest.cpp"

int main(int argc, char **argv){

    QCoreApplication a(argc, argv);
    printf("teste\n");

    initTest( 50000 , 50000000 );

    return 0;
}
