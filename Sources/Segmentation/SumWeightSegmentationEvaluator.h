//
// Created by Guilherme Wachs on 15/06/15.
//

#ifndef PHDTHESIS_SUMWEIGHTSEGMENTATIONEVALUATOR_H
#define PHDTHESIS_SUMWEIGHTSEGMENTATIONEVALUATOR_H


#include <Utilities/IterativeRandomWalk.hpp>
#include <Utilities/GraphUtilities.hpp>
#include "SegmentationEvaluator.hpp"

class SumWeightSegmentationEvaluator : public SegmentationEvaluator {
private:
    FeaturesComplexNetwork::ArcMap<double> weights;
    //IterativeRandomWalk walk;
public:

    SumWeightSegmentationEvaluator(FeaturesComplexNetwork &cn, const QList<const FeatureFactoryAbstract *> &factories)
            : SegmentationEvaluator(cn, factories), weights(cn) {

        GraphUtilities::getWeights(cn, weights);
        GraphUtilities::normalizeOutDegrees(cn, weights, weights);
        GraphUtilities::addAutoLoop(cn, weights);
        GraphUtilities::normalizeOutDegrees(cn, weights, weights);
        //walk.setWeights(weights);
    };

    virtual float evaluate(const SegmentedImage &image);
};


#endif //PHDTHESIS_SUMWEIGHTSEGMENTATIONEVALUATOR_H

