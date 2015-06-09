#ifndef AREA_FEATURE__HPP
#define AREA_FEATURE__HPP

#include "Region.hpp"
#include "FeatureFactoryAbstract.hpp"
#include <memory>


using namespace std;

class AreaFeatureFactory : public FeatureFactoryAbstract {

private:
    int discretization;

    void discretize(int quantization);

public:

    AreaFeatureFactory(int discretization);

    FeatureAbstractPtr CreateFromRegion(const Region *region) const;

    FeatureAbstractPtr CreateFromStream(istream &stream) const;
};


#endif

