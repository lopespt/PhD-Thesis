#ifndef LABELSCOMPLEXNETWORKCONSTRUCTOR_HPP
#define LABELSCOMPLEXNETWORKCONSTRUCTOR_HPP

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/Link.hpp>
#include <QString>
#include <Utilities/DatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <stdio.h>
#include <Utilities/NodeString.hpp>

class LabelsComplexNetworkConstructor
{
private:
    ComplexNetwork<NodeString, Link> &cn;
    DatabaseReader &reader;
public:
    LabelsComplexNetworkConstructor(ComplexNetwork<NodeString, Link>& cn, DatabaseReader &reader);
    void build();
};

#endif // LABELSCOMPLEXNETWORKCONSTRUCTOR_HPP
