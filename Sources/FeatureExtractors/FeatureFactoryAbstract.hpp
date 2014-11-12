#ifndef FEATUREFACTORYABSTRACT_HPP
#define FEATUREFACTORYABSTRACT_HPP

class FeatureAbstract;
class QDataStream;
class Region;

class FeatureFactoryAbstract
{
private:
    int type;
public:
    FeatureFactoryAbstract(int type);
    virtual FeatureAbstract *CreateFromRegion(const Region *r) const = 0;
    virtual FeatureAbstract *CreateFromStream(QDataStream &stream) const = 0 ;
    int getType() const;
};

#endif // FEATUREFACTORYABSTRACT_HPP
