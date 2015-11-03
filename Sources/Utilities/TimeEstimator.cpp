//
// Created by Guilherme Wachs on 26/10/15.
//

#include <math.h>
#include "TimeEstimator.hpp"
#include <stdio.h>

TimeEstimator::TimeEstimator(int totalTicks) : start(0), last(0), totalTicks(totalTicks), ticks(0) {
    cx=0;
    cxx=0;
    cxxx=0;
}

void TimeEstimator::estimate() {
    if(start==last)
        return;

    float dx = ticks-1;
    float dy = last - start;

    cx = dy/dx;
    cxx = pow(dy/dx, 0.5);
    cxxx = pow(dy/dx, 1./3.);
    tx = (time_t) (cx*totalTicks) + start;
    txx = (time_t) (cxx*totalTicks*totalTicks) + start;
    txxx = (time_t) (cxxx*totalTicks*totalTicks*totalTicks) + start;
}

void TimeEstimator::tick(int i) {
    if(ticks==0)
        start=time(NULL);

    last = time(NULL);
    ticks+=i;
}

void TimeEstimator::print() {
    estimate();

    time_t hx,mx,sx;
    time_t hxx,mxx,sxx;
    time_t hxxx,mxxx,sxxx;

    formatTime(tx-last,hx,mx,sx);
    formatTime(txx-last,hxx,mxx,sxx);
    formatTime(txxx-last,hxxx,mxxx,sxxx);

    printf("time left: x=%02ld:%02ld:%02ld  x^2=%02ld:%02ld:%02ld  x^3=%02ld:%02ld:%02ld\n", hx,mx,sx, hxx,mxx,sxx,hxxx,mxxx,sxxx );
}

void TimeEstimator::formatTime(time_t dt, time_t &hour, time_t& min, time_t& sec) {
    sec = (dt%60);
    min = ((dt/60) % 60);
    hour = (dt/60/60);
}

time_t TimeEstimator::getx() const {
    return tx;
}

time_t TimeEstimator::getxx() const {
    return txx;
}

time_t TimeEstimator::getxxx() const {
    return txxx;
}

time_t TimeEstimator::getElapsedTime() const {
    return last-start;
}

int TimeEstimator::getTicks() const{
    return ticks;
}

