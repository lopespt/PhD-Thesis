
#include "Region.hpp"

Region::Region(QImage *image, QPolygon boundary, QString label): image(image),boundary(boundary),  label(label){
}

void Region::show_region() {
    /*l = new QLabel();
    QPixmap p = QPixmap::fromImage(*this->image);
    QPainter e(&p);
    e.setBrush(QBrush(QColor(255,0,0,128)));
    e.drawConvexPolygon(this->boundary);
    l->setPixmap(p);
    l->setVisible(true);*/
}

QRect Region::getBoundaryRect() const {
    return boundary.boundingRect();
}

QPolygon Region::getBoundary() const{
    return this->boundary;
}

QRgb Region::getPixel(int x, int y, bool *insideRegion) const{
    if(insideRegion)
        *insideRegion = this->boundary.containsPoint(QPoint(x,y), Qt::OddEvenFill);
    
    return this->image->pixel(x, y);
}

QRgb Region::getPixelRelative(int x, int y, bool *insideRegion) const{
    x = x + boundary.boundingRect().left();
    y = y + boundary.boundingRect().top();
    return getPixel(x,y, insideRegion);
}

QString Region::getLabel() const{
    return label;
}

cv::Mat Region::getCvImage() const{
    QImage newImg = this->image->convertToFormat(QImage::Format_RGB888);
    cv::Mat ret= cv::Mat(this->image->height(), this->image->width(), CV_8UC3, newImg.bits(), newImg.bytesPerLine()).clone();
    cv::cvtColor(ret,ret, CV_RGB2BGR);
    return ret;
}

cv::Mat Region::getMask() const{
    QImage newImg = this->image->convertToFormat(QImage::Format_RGB888);
    cv::Mat ret= cv::Mat(this->image->height(), this->image->width(), CV_8UC3, newImg.bits(), newImg.bytesPerLine()).clone();
    cv::cvtColor(ret,ret, CV_RGB2BGR);
    return ret;
}

Region::~Region(){
    //if(l)
      //  l->deleteLater();
}
