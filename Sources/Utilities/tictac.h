//
// Created by Guilherme Wachs on 09/08/15.
//

#ifndef PHDTHESIS_TICTAC_H
#define PHDTHESIS_TICTAC_H

#include <time.h>
#include <stdio.h>

namespace tictac{
    time_t _tic;
    time_t _tac;
    void tic(){
        tictac::_tic = time(0);
    }
    void tac(){
        _tac = time(0);
        time_t d = _tac - _tic;
        int s = (int) (d % 60);
        int m = (int) (d % 3600)/60;
        int h = (int) (d)/60/60;
        printf("Time elapsed: %02d:%02d:%02d\n", h,m,s );

    }
}

#endif //PHDTHESIS_TICTAC_H
