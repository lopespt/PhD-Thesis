#include "Region.hpp"

#include <QPixmap>
#include <QPainter>
#include <opencv/highgui.h>

Region::Region(const QImageCV *image, cv::Mat mask) : image(image), label(""), mask(mask) {

}

Region::Region(const QImageCV *image, cv::Mat mask, QString label) : image(image), label(label), mask(mask) {

}

Region::Region(const QImageCV *image, QPolygon boundary, QList<QPolygon> holes) : image(image),
                                                                                  label(""),
                                                                                  mask(image->height(), image->width(),
                                                                                       boundary, holes) {
}

Region::Region(const QImageCV *image, QPolygon boundary) : image(image),
                                                           label(""),
                                                           mask(image->height(), image->width(),
                                                                boundary) {

}

Region::Region(const QImageCV *image, QPolygon boundary, QList<QPolygon> holes, QString label) : image(image),
                                                                                                 label(label),
                                                                                                 mask(image->height(),
                                                                                                      image->width(),
                                                                                                      boundary) {
}

Region::Region(const QImageCV *image, QPolygon boundary, QString label) : image(image),
                                                                          label(label),
                                                                          mask(image->height(),
                                                                               image->width(),
                                                                               boundary) {
}


QRect Region::getBoundaryRect() const {
    return mask.getBoundary().boundingRect();
}


QRgb Region::getPixel(int x, int y, bool *insideRegion) const {
    if (insideRegion)
        *insideRegion = this->mask.containsPoint(x, y);

    return this->image->pixel(x, y);
}

QRgb Region::getPixelRelative(int x, int y, bool *insideRegion) const {
    x = x + mask.getBoundary().boundingRect().left();
    y = y + mask.getBoundary().boundingRect().top();
    return getPixel(x, y, insideRegion);
}

QString Region::getLabel() const {
    return label;
}

const RegionMask &Region::getMask() const {
    return mask;
}

void Region::setImage(QImageCV *img) {
    this->image = img;
}

const QImageCV *Region::getImage() const {
    return this->image;
}


void Region::setMask(const RegionMask &newMask) {
    assert(newMask.size == mask.size);
    this->mask = newMask;
}
