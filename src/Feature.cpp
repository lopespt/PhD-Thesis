
#include "Feature.hpp"

/*
Feature::Feature(float *v, int n):vector(n){
    for(int i=0;i<n;i++){
        this->vector << v[i];
    }
}

Feature::Feature(QVector<float> &other):vector(other){

}*/


Feature::Feature(Region* region):region(region){
}

const QVector<float> & Feature::getVector() const {
    return this->vector;
}

void Feature::printFeature() const{
    printf("v = [");
    for(int i=0;i<vector.size();i++){
        printf("%-.2f", this->vector[i]);
        if(i+1 < vector.size())
            printf(" ,");
    }
    printf("]\n");
}

