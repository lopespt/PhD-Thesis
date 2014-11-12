
#ifndef AREA_FEATURE__HPP
#define AREA_FEATURE__HPP

#include "Region.hpp"
#include "FeatureFactoryAbstract.hpp"

class QDataStream;

class AreaFeatureFactory:public FeatureFactoryAbstract{

    private:
        int discretization;
        void discretize(int quantization);
    public:

        AreaFeatureFactory(int discretization);
        FeatureAbstract* CreateFromRegion(const Region* region) const;
        FeatureAbstract* CreateFromStream(QDataStream &stream) const;
};

#endif

