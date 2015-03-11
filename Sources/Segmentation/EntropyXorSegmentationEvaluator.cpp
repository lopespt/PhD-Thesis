#include "EntropyXorSegmentationEvaluator.hpp"

#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include "SegmentedImage.hpp"
#include <FeatureExtractors/Region.hpp>
#include <Utilities/GraphUtilities.hpp>
#include <Segmentation/CloserNodesGuesser.hpp>
#include <Utilities/Utils.hpp>
#include <algorithm>

EntropyXorSegmentationEvaluator::EntropyXorSegmentationEvaluator(FeaturesComplexNetwork &cn):
    SegmentationEvaluator(cn),
    weights(cn)
{
    GraphUtilities::getWeights(cn, weights);
}

float EntropyXorSegmentationEvaluator::evaluate(const SegmentedImage &image){
    HsvFeatureFactory hsv(18,3,3,200);

    puts("teste1");

    QList<FeatureAbstractPtr> hints;
    for(const Region& r: image.getRegions() ){
        printf("%d\n", r.getImage()->width());
        //hints.append( hsv.CreateFromRegion(&r) );
    }
    puts("teste2");
    IterativeRandomWalk rw(cn, weights);
    CloserNodesGuesser guesser(cn, rw);

    puts("teste3");
    auto x = guesser.guessNodes(hints);
    std::vector<double> weights;
    puts("teste4");
    for (CloserNodesGuesser::NodeProbability xi : x){
        weights.push_back(xi.probability);
    }
    puts("teste5");

    return Utils::entropy< std::vector, double>(weights, weights.size());
}

EntropyXorSegmentationEvaluator::~EntropyXorSegmentationEvaluator()
{

}

