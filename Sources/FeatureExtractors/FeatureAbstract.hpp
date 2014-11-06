#ifndef FEATUREABSTRACT_HPP
#define FEATUREABSTRACT_HPP
#include <string.h>
#include <QtGlobal>

class FeatureAbstractKey;
class FeatureAbstract{
    protected:
        const char *featureName;
        void* data;
        size_t data_size;

    public:
        FeatureAbstract(const char *featureName="Not Defined");
        virtual bool operator<(const FeatureAbstract& other) const;
        virtual const char* asString(char *buffer) const=0;
        const char* getFeatureName() const{
            return featureName;
        }
        virtual ~FeatureAbstract(){}

        bool operator==(const FeatureAbstract& other) const;

        friend uint qHash(const FeatureAbstractKey& v);

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
