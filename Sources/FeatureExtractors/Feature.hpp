
#ifndef FEATURE_HPP
#define FEATURE_HPP

#include "FeatureAbstract.hpp"

template <typename T>
class Feature:public FeatureAbstract{

    protected:
        T content;

    public:
        const T &getContent() const;
        Feature<T>(T value, int type, const char* featureName);
        virtual const char* asString(char* buffer) const = 0 ;
        virtual uint getHash() const = 0;
        virtual void WriteToStream(std::ostream &stream) const = 0;
        virtual ~Feature(){ }
};

template <typename T>
Feature<T>::Feature(T value, int type, const char* featureName):FeatureAbstract(type, featureName){
    this->data = (void*) &content;
    this->data_size = sizeof(T);
    this->content = value;
}

template <typename T>
const T& Feature<T>::getContent() const {
    return this->content;
}

#endif
