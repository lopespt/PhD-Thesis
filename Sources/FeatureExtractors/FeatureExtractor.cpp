
#include "FeatureExtractor.hpp"


FeatureExtractor::FeatureExtractor(const int *discretization):_discretization(discretization){

}

Feature FeatureExtractor::extractFeature(Region* r){
    assert(_discretization!=NULL);
    QVector<float> f = this->doExtraction(r, _discretization);
    return Feature(this->getFeatureName(), f);
}

const int* FeatureExtractor::discretization() const{
    return this->_discretization;
}


