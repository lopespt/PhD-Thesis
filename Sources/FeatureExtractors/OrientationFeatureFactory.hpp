#ifndef ORIENTATIONFEATUREFACTORY_HPP
#define ORIENTATIONFEATUREFACTORY_HPP

#include "FeatureFactoryAbstract.hpp"

class QPoint;
class QList<QPoint>;
class OrientationFeature;


class OrientationFeatureFactory:public FeatureFactoryAbstract
{
private:
    OrientationFeature* discoverOrientation(QList<QPoint> points) const;
    inline float distance(QPoint a, QPoint b) const;

public:
    OrientationFeatureFactory();
    FeatureAbstract* CreateFromRegion(const Region *r) const;
};

#endif // ORIENTATIONFEATUREFACTORY_HPP
