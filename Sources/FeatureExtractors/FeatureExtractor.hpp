

#ifndef FEATURE_EXTRACTOR__HPP
#define FEATURE_EXTRACTOR__HPP

#include "Feature.hpp"
#include "Region.hpp"

class FeatureExtractor{

    private:
        const int* _discretization;

    public:
        FeatureExtractor(const int* discretization=NULL);
        Feature extractFeature(Region* r);
        virtual ~FeatureExtractor(){};
        const int* discretization() const;

    protected:
        virtual QVector<float> doExtraction(const Region* region, const int* discretization){return QVector<float>();};
        virtual const char* getFeatureName(){return NULL;};

};
#endif

