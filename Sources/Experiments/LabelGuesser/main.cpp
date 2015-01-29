
#include "LabelGuesserExperiment.hpp"
#include <locale.h>
#include <QString>

int main(int argc, char *argv[]){
    LabelGuesserExperiment exp;

    exp.execute(argv[1], argv[2]);

    return 0;
}
