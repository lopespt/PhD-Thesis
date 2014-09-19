
#include "SupervisedImage.hpp"

SupervisedImage::SupervisedImage(QString imagePath, QString supervisedPath):imagePath(imagePath), supervisedPath(supervisedPath), image(imagePath){

    parse_xml();
    printf("%s\n%s\n", imagePath.toStdString().c_str(), supervisedPath.toStdString().c_str()); 
}

void SupervisedImage::parse_xml(){
    QRegularExpression exp("<polygon>.*?</polygon>", QRegularExpression::DotMatchesEverythingOption );      

    QFile f(this->supervisedPath);

    f.open(QFile::ReadOnly);
    QByteArray contents = f.readAll().replace('\r','\n');
    f.close();
    auto matches = exp.globalMatch(contents);
    while(matches.hasNext()){
        printf("entrei\n");
        printf("%s\n", matches.next().captured(0).toStdString().c_str());
    }
    printf("passei\n");

}

Region SupervisedImage::createRegion(QString polygonXml){
}
    

void SupervisedImage::show_image(){
    l=new QLabel();
    l->setBaseSize(200,200);
    l->setPixmap(QPixmap::fromImage(image));
    l->setVisible(true);
}

SupervisedImage::~SupervisedImage(){
    if(l)
        l->deleteLater();
}

