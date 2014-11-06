#ifndef FEATURESCOMPLEXNETWORK_HPP
#define FEATURESCOMPLEXNETWORK_HPP
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include "Link.hpp"

class FeaturesComplexNetwork:public ComplexNetwork<const FeatureAbstract*, Link>
{

public:
    FeaturesComplexNetwork();
    void save(const char* filename);
    void load(const char* filename, QList<FeatureAbstract*>);
};

#endif // FEATURESCOMPLEXNETWORK_HPP
