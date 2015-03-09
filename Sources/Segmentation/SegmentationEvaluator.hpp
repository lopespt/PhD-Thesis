#ifndef SEGMENTATIONEVALUATOR_HPP
#define SEGMENTATIONEVALUATOR_HPP

#include <Utilities/FeaturesComplexNetwork.hpp>
class SegmentedImage;

class SegmentationEvaluator
{
protected:
    FeaturesComplexNetwork &cn;
public:
    SegmentationEvaluator(FeaturesComplexNetwork &cn);
    virtual float evaluate(const SegmentedImage &image)=0;
    ~SegmentationEvaluator();
};

#endif // SEGMENTATIONEVALUATOR_HPP
