#ifndef SEGMENTER_H
#define SEGMENTER_H
#include <stdio.h>
#include <QImage>
#include <opencv/cv.h>
#include "SegmentedImage.hpp"
#include <Utilities/Utils.hpp>
class Segmenter
{
public:
    Segmenter();
    SegmentedImage execute(const QImage &img){
        return execute(Utils::QImage2Mat(img));
     }

    virtual SegmentedImage execute(const cv::Mat& m)=0;
    virtual ~Segmenter();
};

#endif // SEGMENTER_H
