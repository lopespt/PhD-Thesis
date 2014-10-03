
#ifndef FEATURE_HPP
#define FEATURE_HPP

#include <QVector>
#include "Region.hpp"

class Feature{

    private:
        const char *featureName;
        QVector<float> vector;

    public:
        const QVector<float> &getVector() const;
        void printFeature() const;
        bool operator<(const Feature& other) const;
        Feature(const char* featureName, float *v, int n);
        Feature(const char* featureName, QVector<float> &other);

};

#endif
