#ifndef LABELSCOMPLEXNETWORKCONSTRUCTOR_HPP
#define LABELSCOMPLEXNETWORKCONSTRUCTOR_HPP

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/Link.hpp>
#include <QString>
#include <Utilities/DatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <stdio.h>
class NodeString{
    public:
        char text[50];
        NodeString(){text[0]='\0';};
        NodeString(const QString& other){
            strcpy(text, other.toStdString().c_str());
        }

        NodeString& operator=(const QString& other){
            strcpy(text, other.toStdString().c_str());
            return *this;
        }
        bool operator<(const QString& other) const{
            return strcmp(text, other.toStdString().c_str()) < 0;
        }
        bool operator<(const NodeString& other)const{
            return strcmp(text, other.text)<0;
        }
        bool operator==(const NodeString& other) const{
            return !(*this < other || other < *this);
        }
};


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
