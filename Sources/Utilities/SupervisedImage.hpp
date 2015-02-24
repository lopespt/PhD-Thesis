
#ifndef SUPERVISED_IMAGE__H
#define SUPERVISED_IMAGE__H

#include <QList>
#include <FeatureExtractors/Region.hpp>
#include <QString>
#include <QImage>
#include <opencv/cv.h>

using namespace std;

class Region;
class SupervisedImage{
    
    private:
        bool alreadyParsed;
        QString imagePath;
        QString supervisedPath;
        QImage image;
        QList<Region> regions;
        mutable cv::Mat hsvImage;
        mutable cv::Mat bgrImage;
        static QPolygon extractPolygon(QString Xml);
        static QString extractLabel(QString Xml);
        void parse_xml();
        

    public:
        SupervisedImage(QString imagePath, QString supervisedPath);
        ~SupervisedImage();
        const QList<Region>& getRegions();
        const QImage* getImage() ;
        QString getImagePath() const;
        QString getSupervisedPath() const;
        cv::Mat getCvBGRImage() const;
        cv::Mat getCvHsvImage() const;

};


#endif


