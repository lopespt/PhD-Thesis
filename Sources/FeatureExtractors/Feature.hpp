
#ifndef FEATURE_HPP
#define FEATURE_HPP

#include <QVector>
#include "Region.hpp"
#include <string.h>
#include "FeatureAbstract.hpp"

template <typename T>
class Feature:public FeatureAbstract{

    protected:
        T content;

    public:
        const T &getContent() const;
        Feature<T>(T value, const char* featureName);
        virtual const char* asString(char *buffer) const;
        virtual ~Feature(){}
};

template <typename T>
Feature<T>::Feature(T value, const char* featureName):FeatureAbstract(featureName){
    this->data = (void*) &content;
    this->data_size = sizeof(T);
    this->content = value;
}

template <typename T>
const T& Feature<T>::getContent() const {
    return this->content;
}

#endif
