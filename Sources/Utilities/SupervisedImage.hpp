
#ifndef SUPERVISED_IMAGE__H
#define SUPERVISED_IMAGE__H

#include <QList>
#include <FeatureExtractors/Region.hpp>
#include <QString>
#include <QImage>


using namespace std;

class SupervisedImage{
    
    private:
        bool alreadyParsed;
        QString imagePath;
        QString supervisedPath;
        QImage image;
        QList<Region> regions;
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

};


#endif


