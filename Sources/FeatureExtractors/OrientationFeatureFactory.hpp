#ifndef ORIENTATIONFEATUREFACTORY_HPP
#define ORIENTATIONFEATUREFACTORY_HPP

#include "FeatureFactoryAbstract.hpp"
#include <QList>
class QPoint;
class OrientationFeature;


class OrientationFeatureFactory:public FeatureFactoryAbstract
{
private:
    int discretization;
    OrientationFeature* discoverOrientation(QList<QPoint> points) const;
    float distance(QPoint a, QPoint b) const;
    int discretize(float min, float max, float d, int val) const;

public:
    OrientationFeatureFactory(int discretization);
    FeatureAbstract* CreateFromRegion(const Region *r) const;
    virtual FeatureAbstract *CreateFromStream(QDataStream &stream) const;
};

#endif // ORIENTATIONFEATUREFACTORY_HPP
