
#ifndef COMPLEX_NETWORK_CONSTRUCTOR__HPP
#define COMPLEX_NETWORK_CONSTRUCTOR__HPP

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <FeatureExtractors/Feature.hpp>
#include "DatabaseReader.hpp"
#include <FeatureExtractors/Region.hpp>
#include "SupervisedImage.hpp"
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <QLinkedList>
#include "Link.hpp"
#include <QHash>
#include <unordered_map>
#include <Utilities/FeaturesComplexNetwork.hpp>

using namespace std;

class ComplexNetworkConstructor{

    private:

        QHash<FeatureAbstractKey , node_id> index;

        FeaturesComplexNetwork &cn;
        DatabaseReader &reader;
        QList<FeatureFactoryAbstract*> extractors;
        unsigned long long int time=1;
        void makeCoOccurrences(QLinkedList<FeatureAbstract*> &features);
        /** Esta é a influência do tempo na aprendizagem \f$ \lambda  \f$ */
        float lambda=1; 
        /** Esta é a taxa de aprendizagem \f$ \alpha  \f$ */
        float learningRate=0.3;
        float recorrencia(float time);

    public:
        ComplexNetworkConstructor(FeaturesComplexNetwork &cn, DatabaseReader &reader, QList<FeatureFactoryAbstract*> extractors);
        void build();

};

ComplexNetworkConstructor::ComplexNetworkConstructor(FeaturesComplexNetwork &cn, DatabaseReader &reader, QList<FeatureFactoryAbstract*> extractors):cn(cn),
    reader(reader),
    extractors(extractors)
{
}

void ComplexNetworkConstructor::build(){
    QLinkedList<FeatureAbstract*> features;
    unsigned int num=1;
    while(reader.hasNext()){
        SupervisedImage img = reader.readNext();
        printf("Reading image(%u/%d): %s%s\n", num, reader.getTotal(), img.getImagePath().size()>60?"...":"",img.getImagePath().right(60).toStdString().c_str());
        features.clear();
        foreach(Region r, img.getRegions()){
            for(QList<FeatureFactoryAbstract*>::iterator i = extractors.begin(); i != extractors.end(); i++){
                FeatureAbstract* f = (*i)->CreateFromRegion(&r);
                features.append(f);
            }
        }
        //printf("Nodes: %ld , Edges: %ld\n", cn.getNumNodes(), cn.getNumEdges());
        makeCoOccurrences(features);
        num++;
    }
    fflush(stdout);
}

/** Atualiza os pesos as arestas de acordo com a Equação:
 * \f[ w_{i,j} = w_{i,j} + \alpha\left(\frac{\lambda}{\Delta t} - w_{i,j} \right)  \f]
 */
void ComplexNetworkConstructor::makeCoOccurrences(QLinkedList<FeatureAbstract*> &features){

    QLinkedList<node_id> nodes;
    foreach(const FeatureAbstract* f, features){
        node_id id;
        if(!index.contains(FeatureAbstractKey(f))){
            id= cn.addNode(f);
            index[FeatureAbstractKey(f)]=id;
        }else{
            id = index[FeatureAbstractKey(f)];
            delete f;
        }
        nodes.append(id);
    }

    float delta_t;
    float weight;

    for(QLinkedList<node_id>::const_iterator it1=nodes.begin();  it1!=nodes.end(); it1++){
        for(QLinkedList<node_id>::const_iterator it2=it1+1; it2!=nodes.end(); it2++){
           Link *e = cn.getEdge( *it1, *it2 );
                if(e){
                    delta_t = this->time - e->getTime();
                    assert(delta_t>0);
                    weight = e->getWeight();
                    //e->setAttribute(Link(0,weight+1));
                    e->setTime(this->time);
                    e->setWeight(weight + learningRate*(recorrencia(delta_t)) - weight);
                    //e->setWeight(weight + 1);
                }else{
                    Link l = Link(this->time, 1 );
                    //e = new Edge<Feature, Link>(cn.getNode(f1), cn.getNode(f2), Link(this->time, this->learningRate*lambda/this->time  ));
                    cn.addEdge(*it1, *it2,  l);
                    //printf("opa novo\n");
                }
            this->time++;
        }
    }
}float ComplexNetworkConstructor::recorrencia(float time){
    float ma=1;
    float mi=0.01;
    float z=8;
    return (ma-mi)*pow(2,(1-time)/(z-1))+mi;
}


#endif
