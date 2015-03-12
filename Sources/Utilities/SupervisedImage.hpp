
#ifndef SUPERVISED_IMAGE__H
#define SUPERVISED_IMAGE__H

#include <QList>
#include <FeatureExtractors/Region.hpp>
#include <QString>
#include <QImage>
#include <opencv/cv.h>
#include <FeatureExtractors/QImageCV.hpp>

using namespace std;

class Region;
class SupervisedImage{
    
    private:
        bool alreadyParsed;
        QString imagePath;
        QString supervisedPath;
        mutable QImageCV image;
        QList<Region> regions;
        static QPolygon extractPolygon(QString Xml);
        static QString extractLabel(QString Xml);
        void parse_xml();
        mutable bool errorState;
        

    public:
        SupervisedImage(QString imagePath, QString supervisedPath);
        ~SupervisedImage();
        const QList<Region>& getRegions();
        const QImageCV* getImage() const;
        QString getImagePath() const;
        QString getSupervisedPath() const;
        cv::Mat getCvBGRImage() const;
        cv::Mat getCvHsvImage() const;
        bool hasError() const;

};


#endif


