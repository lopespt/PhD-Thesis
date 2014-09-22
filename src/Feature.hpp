
#ifndef FEATURE_HPP
#define FEATURE_HPP

#include <QVector>
#include "Region.hpp"

class Feature{

    private:

    public:
        const QVector<float> &getVector() const;
        virtual void extractFeature()=0;
        void printFeature() const;

    protected:
        Region* region;
        QVector<float> vector;
        Feature(Region* region);
        //Feature(float *v, int n);
        //Feature(QVector<float> &other);
    

};

#endif
