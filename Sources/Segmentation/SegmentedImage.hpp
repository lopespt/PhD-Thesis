#ifndef SEGMENTEDIMAGE_HPP
#define SEGMENTEDIMAGE_HPP
#include <QPolygon>
#include <opencv/cv.h>
#include <FeatureExtractors/Region.hpp>
#include <FeatureExtractors/QImageCV.hpp>

using namespace cv;
class SegmentedImage
{
private:
    QImageCV image;
    QVector<Region> regions;

public:
    SegmentedImage(QImageCV img, QVector<Region> regions);

    const QImageCV &getImage() const;
    const QVector<Region>& getRegions() const;


    void showRegion(int i) const;

    ~SegmentedImage();
};

#endif // SEGMENTEDIMAGE_HPP
