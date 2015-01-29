#ifndef FEATUREFACTORYABSTRACT_HPP
#define FEATUREFACTORYABSTRACT_HPP

#include <memory>

class FeatureAbstract;
class QDataStream;
class Region;


using namespace std;
class FeatureFactoryAbstract
{
private:
    int type;
public:
    FeatureFactoryAbstract(int type);
    virtual shared_ptr<FeatureAbstract> CreateFromRegion(const Region *r) const = 0;
    virtual shared_ptr<FeatureAbstract> CreateFromStream(QDataStream &stream) const = 0 ;
    int getType() const;
    virtual ~FeatureFactoryAbstract(){}
};

#endif // FEATUREFACTORYABSTRACT_HPP
