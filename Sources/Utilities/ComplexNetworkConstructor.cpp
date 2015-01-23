
#include "ComplexNetworkConstructor.hpp"
#include <FeatureExtractors/Feature.hpp>
#include <QList>

ComplexNetworkConstructor::ComplexNetworkConstructor(FeaturesComplexNetwork &cn, DatabaseReader &reader, QList<FeatureFactoryAbstract*> extractors):cn(cn),
    reader(reader),
    extractors(extractors)
{
}

void ComplexNetworkConstructor::build(){
    QLinkedList<FeatureAbstract*> features;
    QList<int> regionsIds;
    unsigned int num=1;
    while(reader.hasNext()){
        SupervisedImage img = reader.readNext();
        printf("Reading image(%u/%d): %s%s\n", num, reader.getTotal(), img.getImagePath().size()>60?"...":"",img.getImagePath().right(60).toStdString().c_str());
        features.clear();
        for(int idx=0;idx<img.getRegions().size();idx++){
            Region r = img.getRegions().at(idx);
            for(QList<FeatureFactoryAbstract*>::iterator i = extractors.begin(); i != extractors.end(); i++){
                FeatureAbstract* f = (*i)->CreateFromRegion(&r);
                features.append(f);
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
void ComplexNetworkConstructor::makeCoOccurrences(QLinkedList<FeatureAbstract*> &features, QList<int> &regionsIds){

    QLinkedList<node_id> nodes;
    foreach(const FeatureAbstract* f, features){
        node_id id;
        if(!index.contains(FeatureAbstractKey(f))){
            id= cn.addNode(shared_ptr<const FeatureAbstract>(f));
            index[FeatureAbstractKey(f)]=id;
        }else{
            id = index[FeatureAbstractKey(f)];
            delete f;
        }
        nodes.append(id);
    }

    float delta_t;
    float weight;
    unsigned int i=0,j=0;
    for(QLinkedList<node_id>::const_iterator it1=nodes.begin();  it1!=nodes.end(); it1++){
        j=i+1;
        for(QLinkedList<node_id>::const_iterator it2=it1+1; it2!=nodes.end(); it2++){
           Link *e = cn.getEdge( *it1, *it2 );
                if(e){
                    delta_t = this->time - e->getTime();
                    assert(delta_t>0);
                    weight = e->getWeight();
                    e->setTime(this->time);
                    //e->setWeight(weight + learningRate*(recorrencia(delta_t)) - weight);
                        e->setWeight(weight + 1);
                    if(regionsIds[i] == regionsIds[j])
                        e->isSameLabel(true);
                }else{
                    Link l = Link(this->time, 0.01 );
                    if(regionsIds[i] == regionsIds[j])
                        l.isSameLabel(true);
                    cn.addEdge(*it1, *it2,  l);
                    cn.addEdge(*it2, *it1,  l);
                }
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

