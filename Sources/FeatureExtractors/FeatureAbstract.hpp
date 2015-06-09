#ifndef FEATUREABSTRACT_HPP
#define FEATUREABSTRACT_HPP

#include <string.h>
#include <QtGlobal>
#include <memory>

using namespace std;

class FeaturesComplexNetwork;

class FeatureAbstract {
protected:
    int type;
    const char *featureName;
    void *data;
    size_t data_size;

public:
    FeatureAbstract(int type, const char *featureName = "Not Defined");


    virtual bool operator<(const FeatureAbstract &other) const;

    virtual const char *asString(char *buffer) const = 0;

    virtual uint getHash() const = 0;

    const int getType() const {
        return type;
    }

    const char *getFeatureName() const {
        return featureName;
    }

    virtual void WriteToStream(std::ostream &stream) const = 0;

    virtual bool operator==(const FeatureAbstract &other) const;

    friend class FeaturesComplexNetwork;

    friend std::ostream &operator<<(ostream &os, const shared_ptr<FeatureAbstract> &node);

    virtual ~FeatureAbstract() {
    }
};

class FeatureAbstractPtr {
private:
    shared_ptr<const FeatureAbstract> ptr;
public:
    FeatureAbstractPtr() : ptr() { }

//    FeatureAbstractPtr(const FeatureAbstractPtr &other):ptr(other.ptr){}
//    FeatureAbstractPtr(const FeatureAbstractPtr &&other):ptr(std::move(other.ptr)){}
    FeatureAbstractPtr(FeatureAbstract *ptr) : ptr(ptr) { }

    FeatureAbstractPtr(const FeatureAbstract *ptr) : ptr(ptr, [](const FeatureAbstract *p) {
        printf("deletando ptr\n");
        fflush(stdout);
        delete p;
    }) { }


    bool operator<(const FeatureAbstractPtr &other) const {
        return *this->ptr < *other.ptr;
    }

    bool operator==(const FeatureAbstractPtr &other) const {
        return *this->ptr == *other.ptr;
    }

/*
    FeatureAbstractPtr& operator=(const FeatureAbstractPtr& other) {
        this->ptr = other.ptr;
        return *this;
    }
*/


    const FeatureAbstract *operator->() const {
        return ptr.get();
    }

    const FeatureAbstract *get() const {
        return ptr.get();
    }


    friend ostream &operator<<(ostream &os, const FeatureAbstractPtr &p);

    friend istream &operator>>(istream &is, FeatureAbstractPtr &p);

};

uint qHash(const FeatureAbstractPtr &v);


#endif // FEATUREABSTRACT_HPP
