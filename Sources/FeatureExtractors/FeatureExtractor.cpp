
#include "FeatureExtractor.hpp"

Feature FeatureExtractor::extractFeature(Region* r){
    QVector<float> f = this->doExtraction(r);
    this->doDiscretization(f, _discretization);
    return Feature(this->getFeatureName(), f);
}
void FeatureExtractor::setDiscretization(int i){
    this->_discretization = i;
}

int FeatureExtractor::discretization(){
    return this->_discretization;
}


