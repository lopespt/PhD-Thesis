#ifndef REGION__H
#define REGION__H

#include <QPolygon>
#include <QImage>
#include <QString>

class Region{

    private:
        QPolygon boundary;
        QImage region;
        QString label;

    public:
        Region(QPolygon boundary, QImage image, QString label);

        

};

#endif
