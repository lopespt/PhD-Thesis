//
// Created by Guilherme Wachs on 06/08/15.
//

#include <stdio.h>
#include "FrequentLabels.hpp"

#include <time.h>


int h(time_t t){
    return t/60.0/60;
}
int m(time_t t){
    return (t % 3600)/60;
}
int s(time_t t){
    return t%60;
}

int main(int argc, char *argv[]) {
    time_t inicio = time(0);
    FrequentLabels freq("/Users/wachs/SUN", "saida.txt");
    time_t fim = time(0) - inicio;
    printf("Total: %02d:%02d:%02d\n", h(fim), m(fim), s(fim));
    return 0;
}