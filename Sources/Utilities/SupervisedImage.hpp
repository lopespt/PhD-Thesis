#include <sys/cdefs.h>

#ifndef SUPERVISED_IMAGE__H
#define SUPERVISED_IMAGE__H

#include <QList>
#include <FeatureExtractors/Region.hpp>
#include <QString>
#include <opencv/cv.h>
#include <FeatureExtractors/QImageCV.hpp>

using namespace std;

class SupervisedImage {

private:
    mutable bool alreadyParsed;
    QString imagePath;
    QString supervisedPath;
    mutable QImageCV image;
    mutable QList<Region> regions;

    static QPolygon extractPolygon(QString Xml);

    static QString extractLabel(QString Xml);

    void parse_xml() const;

    mutable bool errorState;


public:
    SupervisedImage(QString imagePath, QString supervisedPath);

    ~SupervisedImage();

    const QList<Region> &getRegions() const;

    const QImageCV *getImage() const;

    QString getImagePath() const;

    QString getSupervisedPath() const;

    cv::Point getImageCenter() const;

    const cv::Mat &  getCvHsvImage() const;

    bool hasError() const;

    const cv::Mat & getCvBGRImage() const;


    void addRegion(QString label, const RegionMask &region);
};

class Region;


#endif


