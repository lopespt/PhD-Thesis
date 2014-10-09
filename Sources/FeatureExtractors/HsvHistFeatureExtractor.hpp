
#ifndef HSVHISTFEATUREEXTRACTOR__HPP
#define HSVHISTFEATUREEXTRACTOR__HPP

#include "FeatureExtractor.hpp"
#include "Region.hpp"


class HsvHistFeatureExtractor:public FeatureExtractor{

    private:
        void discretize(int quantization);
    public:
        HsvHistFeatureExtractor();
        QVector<float> doExtraction(Region* r, int discretization);
        const char* getFeatureName();

};

#endif

