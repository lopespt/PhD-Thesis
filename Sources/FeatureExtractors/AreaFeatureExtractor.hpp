
#ifndef AREA_FEATURE__HPP
#define AREA_FEATURE__HPP

#include <FeatureExtractor.hpp>
#include <Region.hpp>

class AreaFeatureExtractor:public FeatureExtractor{

    private:
        void discretize(int quantization);
    public:
        AreaFeatureExtractor();
        QVector<float> doExtraction(Region* r);
        void doDiscretization(QVector<float> &feature, int discretization);
        const char* getFeatureName();

};

#endif
