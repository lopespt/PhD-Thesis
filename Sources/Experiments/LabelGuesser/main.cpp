
#include "LabelGuesserExperiment.hpp"
#include <locale.h>
#include <QString>
#include <QCoreApplication>

int main(int argc, char *argv[]){

    QCoreApplication app(argc, argv);

    LabelGuesserExperiment exp;
    //exp.execute(argv[1], argv[2]);
    exp.execute("/Users/wachs/SUN", "/Users/wachs/saida.txt");

    return 0;// app.exec();
}
