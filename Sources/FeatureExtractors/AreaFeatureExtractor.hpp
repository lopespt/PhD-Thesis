
#ifndef AREA_FEATURE__HPP
#define AREA_FEATURE__HPP

#include "FeatureExtractorAbstract.hpp"
#include "Region.hpp"

class AreaFeatureExtractor:public FeatureExtractorAbstract{

    private:
        int discretization;
        void discretize(int quantization);
    public:
        AreaFeatureExtractor(int discretization);
        FeatureAbstract* doExtraction(const Region* region);
};

#endif

