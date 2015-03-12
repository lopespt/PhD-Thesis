#include "EntropyXorSegmentationEvaluator.hpp"

#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include "SegmentedImage.hpp"
#include <FeatureExtractors/Region.hpp>
#include <Utilities/GraphUtilities.hpp>
#include <Segmentation/CloserNodesGuesser.hpp>
#include <Utilities/Utils.hpp>
#include <algorithm>

EntropyXorSegmentationEvaluator::EntropyXorSegmentationEvaluator(FeaturesComplexNetwork &cn, QList<const FeatureFactoryAbstract *> factories):
    SegmentationEvaluator(cn, factories),
    weights(cn)
{
    GraphUtilities::getWeights(cn, weights);
}

/*
 * Method 1 - failed
 * float EntropyXorSegmentationEvaluator::evaluate(const SegmentedImage &image){
    HsvFeatureFactory hsv(18,3,3,4);


    QList<FeatureAbstractPtr> hints;
    for(const Region& r: image.getRegions() ){
        hints.append( hsv.CreateFromRegion(&r) );
    }
    IterativeRandomWalk rw(cn, weights);
    CloserNodesGuesser guesser(cn, rw);

    auto x = guesser.guessNodes(hints);
    std::vector<double> weights;
    //printf("size: %d\n", x.size());
    for (CloserNodesGuesser::NodeProbability xi : x){
        weights.push_back(xi.probability);
    }

    return 1./Utils::entropy< std::vector, double>(weights, weights.size());
}*/

float EntropyXorSegmentationEvaluator::evaluate(const SegmentedImage &image){
    FeaturesComplexNetwork::NodeMap<double> probs(cn);

    QList<FeatureAbstractPtr> hints;
    for(const FeatureFactoryAbstract* f: factories){
        for(const Region& r: image.getRegions() ){
            hints.append( f->CreateFromRegion(&r) );
        }
    }


    IterativeRandomWalk rw(cn, weights);
    float grade = 0;
    int found = 0;
    int notFound = 0;
    for(unsigned int h=0; h < hints.size();h++){
        float single_grade = 1;
        //h will be hided
        QList<FeatureAbstractPtr> hints_hided;
        //Copy elements except h
        for(unsigned int i=0;i< hints.size(); i++){
            if(i != h)
                hints_hided.append(hints[i]);
        }

        if(cn.getNodeFromFeature(hints[h]) != INVALID){
            rw.Execute(cn.getNodeFromFeature(hints[h]), 1);
            rw.getAllProbs(probs);
            for(const FeatureAbstractPtr &item: hints_hided){
                FeaturesComplexNetwork::Node n = cn.getNodeFromFeature(item);
                if(cn.valid(n)){
                    single_grade *= (1-probs[n]);
                    found++;
                    //printf("entrei %f\n", single_grade);
                }else{
                    notFound++;
                }
                
            }
        }
        grade = grade + (1-single_grade);
    }
    printf("%%found = %0.2f\n", (found*1.0)/(found+notFound));

    return grade;
}

EntropyXorSegmentationEvaluator::~EntropyXorSegmentationEvaluator()
{

}

