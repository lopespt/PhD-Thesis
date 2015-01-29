
#ifndef AREA_FEATURE__HPP
#define AREA_FEATURE__HPP

#include "Region.hpp"
#include "FeatureFactoryAbstract.hpp"
#include <memory>

class QDataStream;


using namespace std;
class AreaFeatureFactory:public FeatureFactoryAbstract{

    private:
        int discretization;
        void discretize(int quantization);
    public:

        AreaFeatureFactory(int discretization);
        shared_ptr<FeatureAbstract> CreateFromRegion(const Region* region) const;
        shared_ptr<FeatureAbstract> CreateFromStream(QDataStream &stream) const;
};

#endif

