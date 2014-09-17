#include <stdio.h>
#include <QCoreApplication>
#include "ComplexNetwork.hpp"


int main(int argc, char **argv){

    QCoreApplication a(argc, argv);
    printf("teste\n");

    ComplexNetwork<int, float> n;
    
    
    
//    return a.exec();
    return 0;
}
