#ifndef XORSEGMENTATIONEVALUATOR_HPP
#define XORSEGMENTATIONEVALUATOR_HPP

#include "SegmentationEvaluator.hpp"
#include <Utilities/IterativeRandomWalk.hpp>

class EntropyXorSegmentationEvaluator : public SegmentationEvaluator {
private:
    FeaturesComplexNetwork::ArcMap <double> weights;
    IterativeRandomWalk rw;
public:
    EntropyXorSegmentationEvaluator(FeaturesComplexNetwork &cn, QList<const FeatureFactoryAbstract *> factories);

    float evaluate(const SegmentedImage &image);

    ~EntropyXorSegmentationEvaluator();
};

#endif // XORSEGMENTATIONEVALUATOR_HPP
