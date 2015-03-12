#include "SegmentationEvaluator.hpp"

SegmentationEvaluator::SegmentationEvaluator(FeaturesComplexNetwork &cn, QList<const FeatureFactoryAbstract *> factories):
    cn(cn),
    factories(factories)
{

}

SegmentationEvaluator::~SegmentationEvaluator()
{

}

