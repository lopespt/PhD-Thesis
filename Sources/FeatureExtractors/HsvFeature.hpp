#ifndef HSVFEATURE_HPP
#define HSVFEATURE_HPP

#include "Feature.hpp"
#include <vector>

using namespace std;

class HsvFeature : public Feature<vector<int>> {
private:
    static long int total;
public:
    HsvFeature(vector<int> content);

    virtual const char *asString(char *buffer) const;

    uint getHash() const;

    virtual void WriteToStream(std::ostream &stream) const;

    virtual bool operator==(const FeatureAbstract &other) const;

    virtual bool operator<(const FeatureAbstract &other) const;

    ~HsvFeature();
};


#endif // HSVFEATURE_HPP
