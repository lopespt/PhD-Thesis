#include "XorSegmentationEvaluator.hpp"

#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include "SegmentedImage.hpp"
#include <Utilities/GraphUtilities.hpp>
#include <opencv2/highgui/highgui.hpp>

XorSegmentationEvaluator::XorSegmentationEvaluator(FeaturesComplexNetwork &cn,
                                                                 QList<const FeatureFactoryAbstract *> factories) :
        SegmentationEvaluator(cn, factories),
        weights(cn),
        rw(cn)
{
    GraphUtilities::getWeights(cn, weights);
    rw.setWeights(weights);
}

/*
 * Method 1 - failed
 * float XorSegmentationEvaluator::evaluate(const SegmentedImage &image){
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

float XorSegmentationEvaluator::evaluate(const SegmentedImage &image) {

//    namedWindow("win1");
//    namedWindow("win2");
//    imshow("win1", image.getImage().getCvBGRImage());
//    imshow("win2", image.getRegions().last().getMask());
//    waitKey(0);

    FeaturesComplexNetwork::NodeMap <double> probs(cn);

    QList<FeatureAbstractPtr> hints;
    for (const FeatureFactoryAbstract *f: factories) {
        for (const Region &r: image.getRegions()) {
            hints.append(f->CreateFromRegion(&r));
        }
    }


    float grade = 0;
    int found = 0;
    int notFound = 0;
    for (unsigned int h = 0; h < hints.size(); h++) {
        float single_grade = 1;
        //h will be hided
        QList<FeatureAbstractPtr> hints_hided;
        //Copy elements except h
        for (unsigned int i = 0; i < hints.size(); i++) {
            if (i != h)
                hints_hided.append(hints[i]);
        }

        if (cn.getNodeFromFeature(hints[h]) != INVALID) {
            const ListDigraphBase::Node &nfrom = cn.getNodeFromFeature(hints[h]);
            rw.Execute(nfrom, 1);
            rw.getAllProbs(probs);
            for (const FeatureAbstractPtr &item: hints_hided) {
                FeaturesComplexNetwork::Node n = cn.getNodeFromFeature(item);
                if (cn.valid(n)){
                    float weight = probs[n];
                    //printf("probs = %f\n", weight);
                    single_grade *= (1.f - weight);
                    found++;
                    //printf("entrei %f\n", single_grade);
                } else {
                    notFound++;
                }

            }
        }
        grade = grade + (1.f - single_grade);
    }
    double percFound = (found * 1.0) / (found + notFound);
    printf("%%found = %0.2f\n", percFound);

    return (float) ((grade/hints.size())*percFound);
}

XorSegmentationEvaluator::~XorSegmentationEvaluator() {

}

