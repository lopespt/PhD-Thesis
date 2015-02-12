#ifndef FEATUREFACTORYABSTRACT_HPP
#define FEATUREFACTORYABSTRACT_HPP

#include <memory>
#include <vector>
class FeatureAbstract;
class QDataStream;
class Region;
class FeatureAbstractPtr;

using namespace std;
class FeatureFactoryAbstract
{
private:
    int type;
public:

    FeatureFactoryAbstract(int type);
    virtual FeatureAbstractPtr CreateFromRegion(const Region *r) const = 0;
    virtual FeatureAbstractPtr CreateFromStream(istream &stream) const = 0 ;
    int getType() const;
    virtual ~FeatureFactoryAbstract(){}
};


#endif // FEATUREFACTORYABSTRACT_HPP
