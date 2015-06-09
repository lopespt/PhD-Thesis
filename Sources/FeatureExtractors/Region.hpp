#ifndef REGION__H
#define REGION__H


#include <QPolygon>
#include <QString>
#include <opencv/cv.h>
#include <FeatureExtractors/QImageCV.hpp>
#include "RegionMask.h"

class QRect;

class Region {

private:
    const QImageCV *image;
    QString label;
    RegionMask mask;

public:
    Region() { }

    Region(const QImageCV *image, cv::Mat mask);

    Region(const QImageCV *image, cv::Mat mask, QString label);

    Region(const QImageCV *image, QPolygon boundary);

    Region(const QImageCV *image, QPolygon boundary, QList<QPolygon> holes);

    Region(const QImageCV *image, QPolygon boundary, QList<QPolygon> holes, QString label);

    Region(const QImageCV *image, QPolygon boundary, QString label);


    QRect getBoundaryRect() const;


    QRgb getPixel(int x, int y, bool *insideRegion = NULL) const;

    QRgb getPixelRelative(int x, int y, bool *insideRegion = NULL) const;

    QString getLabel() const;

    void setImage(QImageCV *img);

    const QImageCV *getImage() const;

    /**
     * Returns an opencv InputArray representing the region of interest in
     * the original image. The non-zeroed cells are RoI cells.
     */
    const RegionMask &getMask() const;

    void setMask(const RegionMask &newMask);


};

#endif
