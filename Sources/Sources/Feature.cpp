
#include <Feature.hpp>


Feature::Feature(const char* featureName, float *v, int n):featureName(featureName), vector(n){
    for(int i=0;i<n;i++){
        this->vector << v[i];
    }
}

Feature::Feature(const char* featureName, QVector<float> &other):featureName(featureName), vector(other){
    
}



const QVector<float> & Feature::getVector() const {
    return this->vector;
}

void Feature::printFeature() const{
    printf("%s:  v = [", this->featureName);
    for(int i=0;i<vector.size();i++){
        printf("%-.2f", this->vector[i]);
        if(i+1 < vector.size())
            printf(" ,");
    }
    printf("]\n");
}


bool Feature::operator<(const Feature& other) const{
    for(int i=0;i<this->vector.size() && other.vector.size();i++){
        if( this->vector[i] < other.vector[i] )
            return true;
        else if(this->vector[i] > other.vector[i] )
            return false;
    }
    return this->vector.size() < other.vector.size();
}
