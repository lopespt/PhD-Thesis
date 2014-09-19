
#include "SupervisedImage.hpp"

SupervisedImage::SupervisedImage(QString imagePath, QString supervisedPath):imagePath(imagePath), supervisedPath(supervisedPath), image(imagePath){

    parse_xml();
    printf("%s\n%s\n", imagePath.toStdString().c_str(), supervisedPath.toStdString().c_str()); 
}

void SupervisedImage::parse_xml(){
    QRegularExpression exp("<object>.*?</object>", QRegularExpression::DotMatchesEverythingOption );      

    QFile f(this->supervisedPath);

    f.open(QFile::ReadOnly);
    QByteArray contents = f.readAll().replace('\r','\n');
    f.close();
    auto matches = exp.globalMatch(contents);
    while(matches.hasNext()){
        QString regionXml = matches.next().captured(0);
        QPolygon polygon = extractPolygon(regionXml);
        QString label    = extractLabel(regionXml);
        foreach(QPoint x, polygon){
            printf("x = %d\ty = %d\n", x.x(), x.y());
        }
        printf("label = %s\n", label.toStdString().c_str());
        //QImage image = this->image.copy(polygon.boundingRect());
        this->regions << new Region(&this->image, polygon, label);
    }

}

QPolygon SupervisedImage::extractPolygon(QString Xml){
    QRegularExpression exp("<pt>.?<x>.?(\\d*).?</x>.?<y>.?(\\d*).?</y>.?</pt>", QRegularExpression::DotMatchesEverythingOption );      
    auto matches = exp.globalMatch(Xml);
    QPolygon res;
    while(matches.hasNext()){
        auto match = matches.next();
        int x = match.captured(1).toInt();
        int y = match.captured(2).toInt();
        res << QPoint(x,y);
    }
    return res;
}

QString SupervisedImage::extractLabel(QString Xml){
       
    QRegularExpression exp("<name>(.*?)</name>", QRegularExpression::DotMatchesEverythingOption );      
    auto matched = exp.globalMatch(Xml);
    return matched.next().captured(1).remove("\n");

}
    

void SupervisedImage::show_image(){
    l=new QLabel();
    l->setBaseSize(200,200);
    l->setPixmap(QPixmap::fromImage(image));
    l->setVisible(true);
}

const QList<Region*>& SupervisedImage::getRegions() const{
    return this->regions;
}


SupervisedImage::~SupervisedImage(){
    foreach(Region* r, regions)
        delete r;

    if(l)
        l->deleteLater();
}

