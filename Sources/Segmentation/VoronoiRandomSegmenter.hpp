#ifndef VORONOIRANDOMSEGMENTER_HPP
#define VORONOIRANDOMSEGMENTER_HPP

#include "Segmenter.hpp"

class VoronoiRandomSegmenter : public Segmenter {
private:
    unsigned int regions;

    SegmentedImage getNextSegmentation(const QImage &image) const;

public:
    VoronoiRandomSegmenter();

    ~VoronoiRandomSegmenter();

    void setNumberOfRegions(unsigned int regions);

    virtual QList<SegmentedImage> execute(const QImage &img, int nSegmentations);


};

#endif // VORONOIRANDOMSEGMENTER_HPP
