#ifndef SEGMENTEDIMAGE_HPP
#define SEGMENTEDIMAGE_HPP
#include <QImage>
#include <QPolygon>
#include <opencv/cv.h>
#include <FeatureExtractors/Region.hpp>

class SegmentedImage
{
private:
    QImage image;
    QVector<Region> regions;

public:
    SegmentedImage();
    ~SegmentedImage();
};

#endif // SEGMENTEDIMAGE_HPP
