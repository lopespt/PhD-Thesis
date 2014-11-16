#include "OrientationFeatureFactory.hpp"

#include "OrientationFeature.hpp"
#include <QPolygon>
#include <QPoint>
#include "OrientationFeature.hpp"

OrientationFeatureFactory::OrientationFeatureFactory():FeatureFactoryAbstract(2)
{
}

FeatureAbstract* OrientationFeatureFactory::CreateFromRegion(const Region *r) const{
    QPolygon bond = r->getBoundary();
    QPoint leftMost=bond.first();
    QPoint rightMost=bond.first();
    QPoint topMost=bond.first();
    QPoint lowerMost=bond.first();

    for(QPolygon::Iterator p = bond.begin(); p != bond.end(); p++){
        if(p->x() < leftMost.x())
            leftMost  = *p;

        if(p->x() > rightMost.x())
            rightMost = *p;

        if(p->y() > topMost.y())
            topMost = *p;

        if(p->y() < lowerMost.y())
            lowerMost = *p;
    }

    QList<QPoint> points;
    points.append(leftMost);
    points.append(rightMost);
    points.append(topMost);
    points.append(lowerMost);

    return discoverOrientation(points);
}

OrientationFeature* OrientationFeatureFactory::discoverOrientation(QList<QPoint> points) const{
    QPoint p1,p2;
    float distance=0;
    for(auto p=points.begin();p!=points.end();p++){
        for(auto q=points.begin();q!=points.end();q++){
            if( this->distance(*p,*q) > distance){
                p1 = *p;
                p2 = *q;
            }
        }
    }
    QPoint r = (p2 - p1);
    if(r.x()==0){
        return new OrientationFeature(0);
    }

    //return atan2( r.y(), r.x() );

}


float OrientationFeatureFactory::distance(QPoint a, QPoint b) const{
    return sqrt( pow(b.x() - a.x(),2) + pow(b.y() - a.y(),2) );
}




