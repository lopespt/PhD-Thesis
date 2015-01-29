
#include "LabelGuesserExperiment.hpp"
#include <locale.h>
#include <QString>
#include <QCoreApplication>

int main(int argc, char *argv[]){

    QCoreApplication app(argc, argv);

    LabelGuesserExperiment exp;
    exp.execute(argv[1], argv[2]);

    return 0;// app.exec();
}
