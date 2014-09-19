#ifndef REGION__H
#define REGION__H

#include <QPolygon>
#include <QImage>
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QColor>

class Region{

    private:
        QImage *image;
        QPolygon boundary;
        QString label;
        QLabel *l=NULL;

    public:
        Region(QImage *image, QPolygon boundary, QString label);
        void show_region();
        ~Region();

};

#endif
