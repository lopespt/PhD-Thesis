#ifndef IMAGESEGMENTATION_HPP
#define IMAGESEGMENTATION_HPP

#include <QImage>
#include <QVector>
#include <QPolygon>

class ImageSegmentation
{
private:
    QImage image;
    QVector<QPolygon> regions;
public:
    ImageSegmentation(const QImage &image, const QVector<QPolygon>& regions);
    ~ImageSegmentation();
};

#endif // IMAGESEGMENTATION_HPP
