//
// Created by Guilherme Wachs on 08/06/15.
//

#ifndef REGIONMASK_H
#define REGIONMASK_H

#include <opencv/cv.h>
#include <QPolygon>
#include <Utilities/Utils.hpp>

using namespace cv;

class RegionMask : public Mat {
private:
    QPolygon boundary;
    QList<QPolygon> holes;
    static cv::Mat& QPolygon2Mask (cv::Mat& img, const QPolygon external, const QList<QPolygon> & holes);
    static QPolygon& Mask2QPolygon(const cv::Mat &img, QPolygon& poly,  QList<QPolygon> &holes);

public:
    RegionMask(){}
    RegionMask(const Mat&  mask);
    RegionMask(int height, int width);
    RegionMask(int height, int width, const QPolygon& boundary, const QList<QPolygon> &holes = QList<QPolygon>());

    const QPolygon &getBoundary() const;
    const QList<QPolygon> &getHoles() const;

    RegionMask operator - (const RegionMask& other) const;
    RegionMask operator + (const RegionMask& other) const;
    bool containsPoint(int x, int y) const;

};


#endif //REGIONMASK_H
