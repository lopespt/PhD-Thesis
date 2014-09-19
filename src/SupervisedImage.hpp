
#ifndef SUPERVISED_IMAGE__H
#define SUPERVISED_IMAGE__H

#include <list>
#include <QImage>
#include "Region.hpp"
#include <QLabel>
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
        list<Region> regions;
        Region createRegion(QString polygonXml);
        void parse_xml();
        QLabel* l=NULL;

    public:
        SupervisedImage(QString imagePath, QString supervisedPath);
        void show_image();
        ~SupervisedImage();

};


#endif


