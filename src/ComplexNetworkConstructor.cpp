
#include "ComplexNetworkConstructor.hpp"

ComplexNetworkConstructor::ComplexNetworkConstructor(t_cn &cn, DatabaseReader &reader, QList<FeatureExtractor*> extractors):cn(cn), reader(reader), extractors(extractors){
}

void ComplexNetworkConstructor::analyseNext(){
    SupervisedImage* img;
    QLinkedList<Feature> features;
    while( (img = reader.readNext()) !=NULL){
        features.clear();
        foreach(Region *r, img->getRegions()){
            for(QList<FeatureExtractor*>::iterator i = extractors.begin(); i != extractors.end(); i++){
                Feature f = (*i)->extractFeature(r);
                features.append(f);
            }
        }
        delete img;
        printf("Nodes: %ld , Edges: %ld\n", cn.getNumNodes(), cn.getNumEdges());
        makeCoOccurrences(features);

        this->time++;
    }
    printf("Acabou\n");
    fflush(stdout);
}

void ComplexNetworkConstructor::makeCoOccurrences(QLinkedList<Feature> &features){

    foreach(const Feature& f, features){
        if(!cn.getNode(f)){
            cn.addNode(new Node<Feature, Link>(f));
        }
    }


    foreach(const Feature& f1, features){
        foreach(const Feature& f2, features){
            Edge<Feature, Link> *e = cn.getEdge(cn.getNode(f1), cn.getNode(f2));
            if(e){
                float delta_t = e->getAttribute().getTime();
                float weight = e->getAttribute().getWeight();
                e->setAttribute( Link(this->time, weight + learningRate*(lambda / delta_t) - weight));
            }else{
                e = new Edge<Feature, Link>(cn.getNode(f1), cn.getNode(f2), Link(this->time, this->learningRate*lambda/this->time  ));
                cn.addEdge(e);
            }
        }
    }
}
