

#ifndef FEATURE_EXTRACTOR_ABSTRACT__HPP
#define FEATURE_EXTRACTOR_ABSTRACT__HPP

#include "Feature.hpp"
#include "Region.hpp"

class FeatureExtractorAbstract{
    protected:
        FeatureExtractorAbstract(){}
    public:
        virtual ~FeatureExtractorAbstract(){}
        virtual FeatureAbstract* doExtraction(const Region* region) = 0;
};


#endif

