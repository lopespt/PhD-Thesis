#ifndef FEATUREABSTRACT_HPP
#define FEATUREABSTRACT_HPP
#include <string.h>
#include <QtGlobal>

class FeatureAbstractKey;
class FeaturesComplexNetwork;
class FeatureAbstract{
    protected:
        int type;
        const char *featureName;
        void* data;
        size_t data_size;

    public:
        FeatureAbstract(int type, const char *featureName="Not Defined");

        virtual bool operator<(const FeatureAbstract& other) const;
        virtual const char* asString(char* buffer) const=0;
        const int getType() const{
            return type;
        }
        const char* getFeatureName() const{
            return featureName;
        }
        virtual ~FeatureAbstract(){}
        virtual void WriteToStream(QDataStream &stream) const = 0;

        bool operator==(const FeatureAbstract& other) const;

        friend uint qHash(const FeatureAbstractKey& v);
        friend class FeaturesComplexNetwork;

};

class FeatureAbstractKey{
private:

    public:
        const FeatureAbstract* pointer;
        FeatureAbstractKey(const FeatureAbstract* pointer):pointer(pointer){
        }

        bool operator==(const FeatureAbstractKey& other) const{
            return (*this->pointer)==(*other.pointer);
        }

};

uint qHash(const FeatureAbstractKey& v);
#endif // FEATUREABSTRACT_HPP
