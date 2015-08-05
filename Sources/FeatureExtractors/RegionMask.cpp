//
// Created by Guilherme Wachs on 08/06/15.
//

#include "RegionMask.h"

RegionMask::RegionMask(const Mat &mask) : Mat(mask) {
    assert(mask.type() == CV_8UC1);
    Mask2QPolygon(mask, this->boundary, this->holes);
}

RegionMask::RegionMask(int height, int width, const QPolygon &boundary, const QList<QPolygon> &holes) : Mat(height,
                                                                                                            width,
                                                                                                            CV_8UC1, cvScalarAll(0)),
                                                                                                        boundary(
                                                                                                                boundary),
                                                                                                        holes(holes) {
    assert(boundary.size() > 0);
    QPolygon2Mask(*this, boundary, holes);
}

cv::Mat &RegionMask::QPolygon2Mask(cv::Mat &img, const QPolygon external, const QList<QPolygon> &holes) {
    vector<vector<cv::Point> > points;

    Utils::QPolygon2CvPointArray(external, points);
    cv::fillPoly(img, points, cvScalarAll(255), 4);

    for(const QPolygon& hole : holes){
        Utils::QPolygon2CvPointArray(hole, points);
        cv::fillPoly(img, points, cvScalarAll(0),4 );
    }
    return img;
}

QPolygon &RegionMask::Mask2QPolygon(const cv::Mat &img, QPolygon &poly, QList<QPolygon> &holes) {
    poly.clear();
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    cv::findContours(img.clone(), contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_KCOS, cv::Point(0, 0));

    //assert(contours.size() > 0);

    if (contours.size() > 0) {
        for (unsigned int i = 0; i < contours[0].size(); i++) {
            poly.append(QPoint(contours[0][i].x, contours[0][i].y));
        }

        int idHole = hierarchy[0][2];
        for (; idHole != -1; idHole = hierarchy[idHole][0]) {
            QPolygon pnew;
            for (unsigned int i = 0; i < contours[idHole].size(); i++) {
                pnew.append(QPoint(contours[idHole][i].x, contours[idHole][i].y));
            }
            holes.append(pnew);
        }
    }

    return poly;
}

const QPolygon &RegionMask::getBoundary() const {
    return boundary;
}

const QList<QPolygon> &RegionMask::getHoles() const {
    return holes;
}

RegionMask RegionMask::operator+(const RegionMask &other) const{
    RegionMask n(this->clone());
    bitwise_or(n, other, n);
    Mask2QPolygon(n, n.boundary, n.holes);
    return n;
}

RegionMask RegionMask::operator-(const RegionMask &other) const{
    RegionMask n(this->clone());
    RegionMask temp(other.clone());
    bitwise_not(temp,temp);
    bitwise_and(n, temp, n);
    Mask2QPolygon(n, n.boundary, n.holes);
    return n;
}

bool RegionMask::containsPoint(int x, int y) const {
    return this->at<char>(x,y)>0;
}

RegionMask::RegionMask(int height, int width) : Mat(height, width, CV_8UC1, cvScalarAll(0)) {

}

QPoint RegionMask::getCenter() const {
    QPoint center(0,0);
    for(QPoint p: boundary){
        center+=p;
    }
    center.setX((int)  ((center.x() + 0.5) / boundary.size()));
    center.setY((int)  ((center.y() + 0.5) / boundary.size()));
    return center;
}
