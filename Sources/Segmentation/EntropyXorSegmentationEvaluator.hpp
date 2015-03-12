#ifndef XORSEGMENTATIONEVALUATOR_HPP
#define XORSEGMENTATIONEVALUATOR_HPP

#include "SegmentationEvaluator.hpp"

class EntropyXorSegmentationEvaluator: public SegmentationEvaluator
{
private:
    FeaturesComplexNetwork::ArcMap<double> weights;
public:
    EntropyXorSegmentationEvaluator(FeaturesComplexNetwork& cn,  QList<const FeatureFactoryAbstract*> factories);
    float evaluate(const SegmentedImage &image);
    ~EntropyXorSegmentationEvaluator();
};

#endif // XORSEGMENTATIONEVALUATOR_HPP
