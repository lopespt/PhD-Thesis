#ifndef FEATURESCOMPLEXNETWORK_HPP
#define FEATURESCOMPLEXNETWORK_HPP
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <ComplexNetwork/ComplexNetworkV2.hpp>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include "Link.hpp"
#include <QHash>
#include<QList>
#include <memory>
#include <exception>
class FeatureFactoryAbstract;

class FeaturesComplexNetwork:public ComplexNetwork< FeatureAbstractPtr , Link>
{
private:
    QHash<FeatureAbstractKey, Node> featureIndex;
    void load(const char* filename){}

    typedef struct{
        char description[200];
        unsigned int num_nodes;
        unsigned int num_edges;
    }header;

public:
    FeaturesComplexNetwork();
    ~FeaturesComplexNetwork();
    void save(const char* filename);
    void load(const char* filename, QList<FeatureFactoryAbstract* >& l);
    float getOutputDegree(Node) const;
    //bool removeNode(node_id id);
    Node getNodeFromFeature(const FeatureAbstract* f) const;
    void refreshCache();
    
    class NodeReader{
    private:
        QList<FeatureFactoryAbstract*> &factories;
    public:
        NodeReader(QList< FeatureFactoryAbstract* > &factories):factories(factories){

        }

        FeatureAbstractPtr operator()(const string& str){
            std::stringstream stream;
            stream << str;
            int type;
            sscanf(str.c_str(), "%d", &type);
            for(FeatureFactoryAbstract* f : factories){
                if(f->getType() == type){
                    FeatureAbstractPtr feat= f->CreateFromStream(stream);
                    return feat;
                }
            }
            throw new runtime_error("No FeatureFactory Found");
            return FeatureAbstractPtr();
        }

    };
};
#endif // FEATURESCOMPLEXNETWORK_HPP

