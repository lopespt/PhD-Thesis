
#include "Region.hpp"

Region::Region(QImage *image, QPolygon boundary, QString label): image(image),boundary(boundary),  label(label){
}

void Region::show_region() {
    l = new QLabel();
    QPixmap p = QPixmap::fromImage(*this->image);
    QPainter e(&p);
    e.setBrush(QBrush(QColor(255,0,0,128)));
    e.drawConvexPolygon(this->boundary);
    l->setPixmap(p);
    l->setVisible(true);
}


Region::~Region(){
    if(l)
        l->deleteLater();
}
