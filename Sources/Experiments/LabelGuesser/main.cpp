
#include "LabelGuesserExperiment.hpp"
#include <locale.h>
#include <QString>
#include <QCoreApplication>
#include "LabelGuesserExperimentThread.hpp"

int main(int argc, char *argv[]){

    QCoreApplication app(argc, argv);


    LabelGuesserExperimentThread l1(0.7,1, LabelGuesserExperiment::XorProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_1w_Xor.txt");
    l1.start();

    LabelGuesserExperimentThread l2(0.7,1, LabelGuesserExperiment::MultProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_1w_Mult.txt");
    l2.start();

    LabelGuesserExperimentThread l3(0.7,2, LabelGuesserExperiment::XorProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_2w_Xor.txt");
    l3.start();

    LabelGuesserExperimentThread l4(0.7,2, LabelGuesserExperiment::MultProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_2w_Mult.txt");
    l4.start();
/*
    LabelGuesserExperiment exp(0.7, 1, LabelGuesserExperiment::XorProbabilities);
    exp.execute("/Users/wachs/SUN/", "guess_reinf_70p_1w_Xor.txt");

    LabelGuesserExperiment exp2(0.7, 1, LabelGuesserExperiment::MultProbabilities);
    exp2.execute("/Users/wachs/SUN/", "guess_reinf_70p_1w_Mult.txt");

    LabelGuesserExperiment exp3(0.7, 2, LabelGuesserExperiment::XorProbabilities);
    exp3.execute("/Users/wachs/SUN/", "guess_reinf_70p_2w_Xor.txt");

    LabelGuesserExperiment exp4(0.7, 2, LabelGuesserExperiment::MultProbabilities);
    exp4.execute("/Users/wachs/SUN/", "guess_reinf_70p_2w_Mult.txt");
*/
    l1.wait();
    l2.wait();
    l3.wait();
    return 0;
}
