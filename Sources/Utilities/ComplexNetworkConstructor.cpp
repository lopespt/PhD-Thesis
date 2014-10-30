
#include "ComplexNetworkConstructor.hpp"

ComplexNetworkConstructor::ComplexNetworkConstructor(t_cn &cn, DatabaseReader &reader, QList<FeatureExtractor*> extractors):cn(cn), reader(reader), extractors(extractors){
}

void ComplexNetworkConstructor::build(){
    QLinkedList<Feature> features;
    unsigned int num=1;
    while(reader.hasNext()){
        SupervisedImage img = reader.readNext();
        printf("Reading image(%u/%d): %s%s\n", num, reader.getTotal(), img.getImagePath().size()>60?"...":"",img.getImagePath().right(60).toStdString().c_str());
        features.clear();
        foreach(Region r, img.getRegions()){
            for(QList<FeatureExtractor*>::iterator i = extractors.begin(); i != extractors.end(); i++){
                Feature f = (*i)->extractFeature(&r);
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
void ComplexNetworkConstructor::makeCoOccurrences(QLinkedList<Feature> &features){

    foreach(const Feature& f, features){
        if(!cn.getNode(f)){
            cn.addNode(new Node<Feature, Link>(f));
        }
    }


    float delta_t;
    float weight;

    //foreach(const Feature& f1, features){
      //  foreach(const Feature& f2, features){
      for(QLinkedList<Feature>::const_iterator it1=features.begin();  it1!=features.end(); it1++){
          for(QLinkedList<Feature>::const_iterator it2=it1+1; it2!=features.end(); it2++){
            Edge<Feature, Link> *e = cn.getEdge(cn.getNode(*it1), cn.getNode(*it2));
            if(e){
                delta_t = this->time - e->getAttribute().getTime();
                assert(delta_t>0);
                weight = e->getAttribute().getWeight();
                //e->setAttribute(Link(0,weight+1));
                e->setAttribute(Link(this->time, weight + learningRate*(1.0 + lambda / delta_t*1.0) - weight));
                //printf("Antes: %.4f\nDepois:%.4f\n", weight, e->getAttribute().getWeight());
            }else{
                e = new Edge<Feature, Link>(cn.getNode(*it1), cn.getNode(*it2), Link(this->time, 1 ));
                //e = new Edge<Feature, Link>(cn.getNode(f1), cn.getNode(f2), Link(this->time, this->learningRate*lambda/this->time  ));
                cn.addEdge(e);
            }
            this->time++;
        }
    }
}


