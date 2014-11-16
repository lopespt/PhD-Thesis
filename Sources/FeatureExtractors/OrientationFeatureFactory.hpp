#ifndef ORIENTATIONFEATUREFACTORY_HPP
#define ORIENTATIONFEATUREFACTORY_HPP

#include "FeatureFactoryAbstract.hpp"
#include <QList>
class QPoint;
class OrientationFeature;


class OrientationFeatureFactory:public FeatureFactoryAbstract
{
private:
    OrientationFeature* discoverOrientation(QList<QPoint> points) const;
    float distance(QPoint a, QPoint b) const;

public:
    OrientationFeatureFactory();
    FeatureAbstract* CreateFromRegion(const Region *r) const;
};

#endif // ORIENTATIONFEATUREFACTORY_HPP
