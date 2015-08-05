#ifndef XORSEGMENTATIONEVALUATOR_HPP
#define XORSEGMENTATIONEVALUATOR_HPP

#include "SegmentationEvaluator.hpp"
#include <Utilities/IterativeRandomWalk.hpp>

class XorSegmentationEvaluator : public SegmentationEvaluator {
private:
    FeaturesComplexNetwork::ArcMap <double> weights;
    IterativeRandomWalk rw;
public:
    XorSegmentationEvaluator(FeaturesComplexNetwork &cn, QList<const FeatureFactoryAbstract *> factories);

    float evaluate(const SegmentedImage &image);

    ~XorSegmentationEvaluator();
};

#endif // XORSEGMENTATIONEVALUATOR_HPP
