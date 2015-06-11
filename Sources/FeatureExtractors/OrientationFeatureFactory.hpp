#ifndef ORIENTATIONFEATUREFACTORY_HPP
#define ORIENTATIONFEATUREFACTORY_HPP

#include "FeatureFactoryAbstract.hpp"
#include <QList>
#include <QPoint>

class QPoint;

class OrientationFeature;

using namespace std;

class OrientationFeatureFactory : public FeatureFactoryAbstract {
private:
    unsigned int discretization;

    OrientationFeature *discoverOrientation(QList<QPoint> points) const;

    float distance(QPoint a, QPoint b) const;

    unsigned int discretize(unsigned int d, float val) const;

public:
    OrientationFeatureFactory() : OrientationFeatureFactory(10) {

    }

    OrientationFeatureFactory(unsigned int discretization);

    FeatureAbstractPtr CreateFromRegion(const Region *r) const;

    FeatureAbstractPtr CreateFromStream(istream &stream) const;
};

#endif // ORIENTATIONFEATUREFACTORY_HPP
