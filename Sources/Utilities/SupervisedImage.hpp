
#ifndef SUPERVISED_IMAGE__H
#define SUPERVISED_IMAGE__H

#include <QList>
#include <QImage>
#include <FeatureExtractors/Region.hpp>
#include <QPixmap>
#include <QObject>
#include <QRegularExpression>
#include <QFile>
#include <QtAlgorithms>

using namespace std;

class SupervisedImage{
    
    private:
        QString imagePath;
        QString supervisedPath;
        QImage image;
        QList<Region*> regions;
        static QPolygon extractPolygon(QString Xml);
        static QString extractLabel(QString Xml);
        void parse_xml();
        

    public:
        SupervisedImage(QString imagePath, QString supervisedPath);
        void show_image();
        ~SupervisedImage();
        const QList<Region*>& getRegions() const;
        const QImage* getImage() const;
        QString getImagePath() const;
        QString getSupervisedPath() const;

};


#endif


