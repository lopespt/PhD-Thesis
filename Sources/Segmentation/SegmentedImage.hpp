#ifndef SEGMENTEDIMAGE_HPP
#define SEGMENTEDIMAGE_HPP
#include <QPolygon>
#include <opencv/cv.h>
#include <FeatureExtractors/Region.hpp>
#include <FeatureExtractors/QImageCV.hpp>
#include <QList>

using namespace cv;
class SegmentedImage
{
private:
    QImageCV image;
    QList<Region> regions;

public:
    SegmentedImage(QImageCV img, QList<Region> regions);
    SegmentedImage(const SegmentedImage& other);

    const QImageCV &getImage() const;
    const QList<Region>& getRegions() const;


    void showRegion(int i) const;

    ~SegmentedImage();
};

#endif // SEGMENTEDIMAGE_HPP
