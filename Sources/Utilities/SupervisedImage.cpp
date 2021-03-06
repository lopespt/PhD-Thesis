#include "SupervisedImage.hpp"
#include <QPixmap>
#include <QRegularExpression>
#include <QFile>
#include <opencv2/highgui/highgui.hpp>

SupervisedImage::SupervisedImage(QString imagePath, QString supervisedPath) : alreadyParsed(false),
                                                                              imagePath(imagePath),
                                                                              supervisedPath(supervisedPath),
                                                                              errorState(false) {
}


void SupervisedImage::parse_xml() const {
    if (alreadyParsed)
        return;
    getImage();

    QRegularExpression exp("<object>.*?</object>", QRegularExpression::DotMatchesEverythingOption);

    QFile f(this->supervisedPath);

    f.open(QFile::ReadOnly);
    QByteArray contents = f.readAll().replace('\r', '\n');
    f.close();
    auto matches = exp.globalMatch(contents);
    while (matches.hasNext()) {
        QString regionXml = matches.next().captured(0);
        QPolygon polygon = extractPolygon(regionXml);
        polygon = polygon.intersected(QPolygon(QRect(0, 0, image.width() - 1, image.height() - 1)));
        QString label = extractLabel(regionXml);
        label.prepend('\"').append('\"');
        if (polygon.size() != 0) {
            this->regions << (Region(&this->image, polygon, label));
        }
    }
    alreadyParsed = true;

}

QPolygon SupervisedImage::extractPolygon(QString Xml) {
    QRegularExpression exp("<pt>.?<x>.?(\\d*).?</x>.?<y>.?(\\d*).?</y>.?</pt>",
                           QRegularExpression::DotMatchesEverythingOption);
    auto matches = exp.globalMatch(Xml);
    QPolygon res;
    while (matches.hasNext()) {
        auto match = matches.next();
        int x = match.captured(1).toInt();
        int y = match.captured(2).toInt();
        res << QPoint(x, y);
    }
    return res;
}


QString SupervisedImage::extractLabel(QString Xml) {

    QRegularExpression exp("<name>(.*?)</name>", QRegularExpression::DotMatchesEverythingOption);
    auto matched = exp.globalMatch(Xml);
    return matched.next().captured(1).remove("\n");

}


const QList<Region> &SupervisedImage::getRegions() const {
    parse_xml();
    return this->regions;
}


const QImageCV *SupervisedImage::getImage() const {
    if (image.isNull()) {
        if (!image.load(this->imagePath)) {
            warn("Error reading image: %s\n", this->imagePath.toStdString().c_str());
            errorState = true;
        }
    }
    return &this->image;
}

QString SupervisedImage::getImagePath() const {
    return this->imagePath;
}

QString SupervisedImage::getSupervisedPath() const {
    return this->supervisedPath;
}

const Mat &  SupervisedImage::getCvBGRImage() const {
    return this->image.getCvBGRImage();
}

const cv::Mat&  SupervisedImage::getCvHsvImage() const {
    return this->image.getCvHsvImage();
}

bool SupervisedImage::hasError() const {
    getImage();
    return errorState;
}

SupervisedImage::~SupervisedImage() {
}

void SupervisedImage::addRegion(QString label, const RegionMask &region) {
    parse_xml();

    QMutableListIterator<Region> it(regions);

    while(it.hasNext()){
        Region& rm = it.next();
        rm.setMask(rm.getMask() - region);
        if (cv::countNonZero(rm.getMask()) == 0)
            it.remove();
    }

    regions << Region(getImage(), region, label);
}

cv::Point SupervisedImage::getImageCenter() const {
    return cv::Point_<int>((int) (image.width() / 2 + 0.5), (int) (image.height() / 2 + 0.5));
}
