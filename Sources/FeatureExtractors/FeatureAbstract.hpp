#ifndef FEATUREABSTRACT_HPP
#define FEATUREABSTRACT_HPP
#include <string.h>
#include <QtGlobal>
#include <memory>

using namespace std;
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

        virtual void WriteToStream(std::ostream &stream) const = 0;

        bool operator==(const FeatureAbstract& other) const;

        friend uint qHash(const FeatureAbstractKey& v);
        friend class FeaturesComplexNetwork;

        friend std::ostream & operator<<(ostream& os, const shared_ptr<FeatureAbstract>& node);

        virtual ~FeatureAbstract(){
        }
};

class FeatureAbstractPtr{
private:
    shared_ptr<const FeatureAbstract> ptr;
public:
    FeatureAbstractPtr():ptr(){}
    FeatureAbstractPtr(const FeatureAbstract* ptr):ptr(ptr){}

    bool operator<(const FeatureAbstractPtr& other) const{
        return *this->ptr < *other.ptr;
    }

    /*const FeatureAbstractPtr& operator=(const FeatureAbstractPtr& other){
         this->ptr = move(other.ptr);
        return *this;
    }*/

    const FeatureAbstract* operator -> (){
        return ptr.get();
    }

    const FeatureAbstract* get() const{
        return ptr.get();
    }



    friend ostream& operator<<(ostream& os, const FeatureAbstractPtr& p);
    friend istream& operator>>(istream& is, FeatureAbstractPtr& p);
};

class FeatureAbstractKey{
private:

    public:
        const FeatureAbstract* pointer;

        FeatureAbstractKey(const FeatureAbstractPtr& pointer):pointer(pointer.get()){

        }

        FeatureAbstractKey(const FeatureAbstract* pointer):pointer(pointer){
        }

        bool operator==(const FeatureAbstractKey& other) const{
            return (*this->pointer)==(*other.pointer);
        }

};

uint qHash(const FeatureAbstractKey& v);

#endif // FEATUREABSTRACT_HPP
