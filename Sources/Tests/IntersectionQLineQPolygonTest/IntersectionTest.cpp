//
// Created by Guilherme Wachs on 26/06/15.
//

#include <qpolygon.h>
#include "IntersectionTest.h"
#include <opencv/cv.h>
#include <Utilities/Utils.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <FeatureExtractors/ShapeSignatureFeatureFactory.h>
#include <FeatureExtractors/Region.hpp>

void IntersectionTest::start() {
    QPolygon poly;
    poly.append(QPoint(0,0));
    poly.append(QPoint(0,100));
    poly.append(QPoint(100,100));
    poly.append(QPoint(100,0));
    cv::Mat mat(200,200, CV_8UC1);

    ShapeSignatureFeatureFactory factory(5, 5);
    //factory.CreateFromRegion();
    QImageCV image(mat.clone());
    Region r(&image, mat);
    Utils::QPolygon2Mask(mat, poly);
    cv::imshow("img", mat);
    cv::waitKey(0);


}
