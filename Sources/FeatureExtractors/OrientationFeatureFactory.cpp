#include "OrientationFeatureFactory.hpp"

#define _USE_MATH_DEFINES

#include "OrientationFeature.hpp"
#include <QPolygon>
#include <cmath>
#include "Region.hpp"


OrientationFeatureFactory::OrientationFeatureFactory(unsigned int discretization) : FeatureFactoryAbstract(2),
                                                                           discretization(discretization) {
}

FeatureAbstractPtr OrientationFeatureFactory::CreateFromRegion(const Region *r) const {
    QList<QPoint> bond = r->getMask().getBoundary().toList();

//    QPoint leftMost = bond.first();
//    QPoint rightMost = bond.first();
//    QPoint topMost = bond.first();
//    QPoint lowerMost = bond.first();
//    for (QPolygon::Iterator p = bond.begin(); p != bond.end(); p++) {
//        if (p->x() < leftMost.x())
//            leftMost = *p;
//
//        if (p->x() > rightMost.x())
//            rightMost = *p;
//
//        if (p->y() > topMost.y())
//            topMost = *p;
//
//        if (p->y() < lowerMost.y())
//            lowerMost = *p;
//    }

//    QList<QPoint> points;
//    points.append(leftMost);
//    points.append(rightMost);
//    points.append(topMost);
//    points.append(lowerMost);

    return FeatureAbstractPtr(discoverOrientation(bond));
}

FeatureAbstractPtr OrientationFeatureFactory::CreateFromStream(istream &stream) const {
    unsigned int i;
    stream.read((char *) &i, sizeof(unsigned int));
    return FeatureAbstractPtr(new OrientationFeature(i));
}

unsigned int OrientationFeatureFactory::discretize(unsigned int d, float val) const {
    unsigned int ret = (unsigned int) (val/360.f * d + 0.5);
    return ret;
}

OrientationFeature *OrientationFeatureFactory::discoverOrientation(QList<QPoint> points) const {
    QPoint p1, p2;

    float distance = 0;
    for (auto p = points.begin(); p != points.end(); ++p) {
        for (auto q = points.begin(); q != points.end(); ++q) {
            float dist = this->distance(*p, *q);
            if (dist > distance) {
                p1 = *p;
                p2 = *q;
                distance = dist;
            }
        }
    }
    QPoint r = (p2 - p1);
    double angle;
    if(r.x() == 0) {
        angle = 90;
    }else{
        angle = (atan2(r.y(), r.x()) * 180. / M_PI);
    }
    unsigned int v = discretize(discretization, (float) angle);
    //printf("lbl = %f %d \n", angle, v );
    return new OrientationFeature(v);
}


float OrientationFeatureFactory::distance(QPoint a, QPoint b) const {
    return (float) sqrt(pow(b.x() - a.x(), 2) + pow(b.y() - a.y(), 2));
}




