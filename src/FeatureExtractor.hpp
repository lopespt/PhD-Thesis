

#ifndef FEATURE_EXTRACTOR__HPP
#define FEATURE_EXTRACTOR__HPP

#include "Feature.hpp"
#include "Region.hpp"

class FeatureExtractor{

    private:
        int _discretization;

    public:
        Feature extractFeature(Region* r);
        void setDiscretization(int i);
        int discretization();
        virtual ~FeatureExtractor(){};

    protected:
        virtual QVector<float> doExtraction(Region* ){return QVector<float>();};
        virtual void doDiscretization(QVector<float> &, int ){};
        virtual const char* getFeatureName(){return NULL;};

};
#endif

