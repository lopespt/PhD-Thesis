#ifndef VORONOIRANDOMSEGMENTER_HPP
#define VORONOIRANDOMSEGMENTER_HPP

#include "Segmenter.hpp"

class VoronoiRandomSegmenter : public Segmenter
{
public:
    VoronoiRandomSegmenter();
    ~VoronoiRandomSegmenter();

    virtual SegmentedImage execute(const cv::Mat &img);


};

#endif // VORONOIRANDOMSEGMENTER_HPP
