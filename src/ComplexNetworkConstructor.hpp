
#ifndef COMPLEX_NETWORK_CONSTRUCTOR__HPP
#define COMPLEX_NETWORK_CONSTRUCTOR__HPP

#include "ComplexNetwork.hpp"
#include "Feature.hpp"
#include "DatabaseReader.hpp"
#include "Region.hpp"
#include "SupervisedImage.hpp"
#include "AreaFeatureExtractor.hpp"

class ComplexNetworkConstructor{

    private:
        ComplexNetwork<Feature, float> &cn;
        DatabaseReader &reader;
        QList<FeatureExtractor*> extractors;

    public:
        ComplexNetworkConstructor(ComplexNetwork<Feature, float> &cn, DatabaseReader &reader, QList<FeatureExtractor*> extractors);
        void analyseNext();

};

#endif
