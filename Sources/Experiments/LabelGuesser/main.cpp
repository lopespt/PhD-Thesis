
#include "LabelGuesserExperiment.hpp"
#include <locale.h>
#include <QString>

int main(int argc, char *argv[]){
    LabelGuesserExperiment exp;

    exp.execute(argv[1]);

    return 0;
}
