//
// Created by Guilherme Wachs on 18/06/15.
//

#ifndef PHDTHESIS_SHAPESIGNATUREFEATURE_H
#define PHDTHESIS_SHAPESIGNATUREFEATURE_H

#include <vector>
#include "FeatureAbstract.hpp"
#include "Feature.hpp"

using namespace std;

class ShapeSignatureFeature : public Feature<vector<int>> {
private:
public:
    ShapeSignatureFeature(vector<int> content);
    virtual const char *asString(char *buffer) const;

    uint getHash() const;

    virtual void WriteToStream(std::ostream &stream) const;

    virtual bool operator==(const FeatureAbstract &other) const;

    virtual bool operator<(const FeatureAbstract &other) const;
};


#endif //PHDTHESIS_SHAPESIGNATUREFEATURE_H

