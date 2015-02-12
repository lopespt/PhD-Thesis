
#include "ComplexNetworkConstructor.hpp"
#include <FeatureExtractors/Feature.hpp>
#include <QList>

ComplexNetworkConstructor::ComplexNetworkConstructor(FeaturesComplexNetwork &cn, DatabaseReader &reader, QList<FeatureFactoryAbstract*> extractors):cn(cn),
    reader(reader),
    extractors(extractors)
{
}

void ComplexNetworkConstructor::build(){

    QList<int> regionsIds;
    unsigned int num=1;
    while(reader.hasNext()){
        QLinkedList< FeatureAbstractPtr > features;
        SupervisedImage img = reader.readNext();
        printf("Reading image(%u/%d): %s%s\n", num, reader.getTotal(), img.getImagePath().size()>60?"...":"",img.getImagePath().right(60).toStdString().c_str());
        
        for(int idx=0;idx<img.getRegions().size();idx++){
            Region r = img.getRegions().at(idx);
            for(QList<FeatureFactoryAbstract*>::iterator i = extractors.begin(); i != extractors.end(); i++){
                features.append(move((*i)->CreateFromRegion(&r)));
                regionsIds.append(idx);
            }
        }
        //printf("Nodes: %ld , Edges: %ld\n", cn.getNumNodes(), cn.getNumEdges());
        makeCoOccurrences(features, regionsIds);
        num++;
    }
    fflush(stdout);
}

/** Atualiza os pesos as arestas de acordo com a Equação:
 * \f[ w_{i,j} = w_{i,j} + \alpha\left(\frac{\lambda}{\Delta t} - w_{i,j} \right)  \f]
 */
void ComplexNetworkConstructor::makeCoOccurrences(QLinkedList<FeatureAbstractPtr>  features, QList<int> &regionsIds){


    QLinkedList<FeaturesComplexNetwork::Node> nodes;

    for(auto f: features){
        FeaturesComplexNetwork::Node id;
        if(!index.contains(FeatureAbstractKey(f.get()))){
            id = cn.addNode(move(f));
            index[FeatureAbstractKey(f.get())]=id;
        }else{
            id = index[FeatureAbstractKey(f.get())];
        }
        nodes.append(id);
    }

    unsigned int i=0,j=0;
    //printf("making coocurrences\n");
    //fflush(stdout);

    for(QLinkedList<FeaturesComplexNetwork::Node>::const_iterator it1=nodes.begin();  it1!=nodes.end(); it1++){
        j=i+1;
        for(QLinkedList<FeaturesComplexNetwork::Node>::const_iterator it2=it1+1; it2!=nodes.end(); it2++){
            reinforceLink(*it1, *it2, regionsIds[i] == regionsIds[j]);
            if(*it2 != *it1)
                reinforceLink(*it2, *it1, regionsIds[i] == regionsIds[j]);
            this->time++;
            j++;
        }
        i++;
    }
}

float ComplexNetworkConstructor::recorrencia(float time){
    float ma=1;
    float mi=0.01;
    float z=lambda;
    return (ma-mi)*pow(2,(1-time)/(z-1))+mi;
}


void ComplexNetworkConstructor::reinforceLink(const FeaturesComplexNetwork::Node& a,const FeaturesComplexNetwork::Node& b, bool isSameLabel){
    float delta_t;
    float weight;
    if(cn.arcExists(a, b) ){
        Link *e = &cn.getArcValue(a, b );
        delta_t = this->time - e->getTime();
        assert(delta_t>0);
        weight = e->getWeight();
        e->setTime(this->time);
        //e->setWeight(weight + learningRate*(recorrencia(delta_t)) - weight);
        e->setWeight(weight + 1);
        e->isSameLabel(isSameLabel);
    }else{
        //Link l = Link(this->time, 0.01 );
        Link l = Link(this->time, 1 );
        l.isSameLabel(isSameLabel);
        cn.addArc(a, b,  l);
    }
}
