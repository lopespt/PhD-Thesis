
#ifndef HSVHISTFEATUREEXTRACTOR__HPP
#define HSVHISTFEATUREEXTRACTOR__HPP

#include "FeatureExtractor.hpp"
#include "Region.hpp"


class HsvHistFeatureExtractor:public FeatureExtractor{

    private:
        void discretize(int quantization);
    public:
        HsvHistFeatureExtractor(const int * discretization);
        QVector<float> doExtraction(const Region* r,const int* discretization);
        const char* getFeatureName();

};

#endif

