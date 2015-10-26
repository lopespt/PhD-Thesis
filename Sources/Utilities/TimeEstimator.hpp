//
// Created by Guilherme Wachs on 26/10/15.
//

#ifndef PHDTHESIS_TIMEESTIMATOR_HPP
#define PHDTHESIS_TIMEESTIMATOR_HPP
#include <list>
#include <time.h>


class TimeEstimator {

private:
    time_t start;
    time_t last;
    int totalTicks;
    int ticks;
    double cx;
    double cxx;
    double cxxx;
    time_t tx;
    time_t txx;
    time_t txxx;

    void estimate();
    static void formatTime(time_t dt, time_t& hour, time_t& min, time_t& sec);
public:
    TimeEstimator(int totalTicks);
    void tick();
    void print();
    time_t getx() const;
    time_t getxx() const;
    time_t getxxx() const;
    time_t getElapsedTime() const;

    int getTicks() const;
};


#endif //PHDTHESIS_TIMEESTIMATOR_HPP
