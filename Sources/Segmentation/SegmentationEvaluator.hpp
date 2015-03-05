#ifndef SEGMENTATIONEVALUATOR_HPP
#define SEGMENTATIONEVALUATOR_HPP

#include <Utilities/FeaturesComplexNetwork.hpp>

class SegmentationEvaluator
{
private:
    const FeaturesComplexNetwork &cn;
public:
    SegmentationEvaluator(const FeaturesComplexNetwork &cn);
    float evaluate();
    ~SegmentationEvaluator();
};

#endif // SEGMENTATIONEVALUATOR_HPP
