#ifndef REGION__H
#define REGION__H

#include <QPolygon>
#include <QImage>
#include <QString>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QPoint>
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
        QRect getBoundaryRect() const;
        QRgb getPixel(int x, int y, bool *insideRegion=NULL) const;
        QRgb getPixelRelative(int x, int y, bool *insideRegion=NULL) const;
        QString getLabel() const;
        

};

#endif
