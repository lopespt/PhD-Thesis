#ifndef SEGMENTER_H
#define SEGMENTER_H

#include <stdio.h>
#include <QImage>
#include <opencv/cv.h>
#include "SegmentedImage.hpp"
#include <Utilities/Utils.hpp>
#include <QList>

class Segmenter {
public:
    Segmenter();

    virtual QList<SegmentedImage> execute(const QImage &img, int nSegmentations) = 0;

    virtual ~Segmenter();
};

#endif // SEGMENTER_H
