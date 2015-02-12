
#include "LabelGuesserExperiment.hpp"
#include <locale.h>
#include <QString>
#include <QCoreApplication>

int main(int argc, char *argv[]){

    QCoreApplication app(argc, argv);

    LabelGuesserExperiment exp(0.7, 1, LabelGuesserExperiment::XorProbabilities);
    exp.execute("/Users/wachs/SUN/", "guess_70p_1w_Xor.txt");

    LabelGuesserExperiment exp2(0.7, 1, LabelGuesserExperiment::MultProbabilities);
    exp2.execute("/Users/wachs/SUN/", "guess_70p_1w_Mult.txt");

    LabelGuesserExperiment exp3(0.7, 2, LabelGuesserExperiment::XorProbabilities);
    exp3.execute("/Users/wachs/SUN/", "guess_70p_2w_Xor.txt");

    LabelGuesserExperiment exp4(0.7, 2, LabelGuesserExperiment::MultProbabilities);
    exp4.execute("/Users/wachs/SUN/", "guess_70p_2w_Mult.txt");
    return 0;// app.exec();
}
