#ifndef ORIENTATIONFEATUREFACTORY_HPP
#define ORIENTATIONFEATUREFACTORY_HPP

#include "FeatureFactoryAbstract.hpp"
#include <QList>

class QPoint;

class OrientationFeature;

using namespace std;

class OrientationFeatureFactory : public FeatureFactoryAbstract {
private:
    int discretization;

    OrientationFeature *discoverOrientation(QList<QPoint> points) const;

    float distance(QPoint a, QPoint b) const;

    int discretize(float min, float max, float d, int val) const;

public:
    OrientationFeatureFactory() : OrientationFeatureFactory(10) {

    }

    OrientationFeatureFactory(int discretization);

    FeatureAbstractPtr CreateFromRegion(const Region *r) const;

    FeatureAbstractPtr CreateFromStream(istream &stream) const;
};

#endif // ORIENTATIONFEATUREFACTORY_HPP
