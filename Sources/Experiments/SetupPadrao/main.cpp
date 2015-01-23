
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <FeatureExtractors/Region.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/RandomWalk.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <QList>
#include <ComplexNetwork/BreadFirstRandomWalk.hpp>
#include <Utilities/RandomWalk.hpp>
#include <Utilities/FeaturesComplexNetwork.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/LabelFeature.hpp>
#include <QList>
#include <Utilities//IterativeRandomWalk.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

class getWeight{
public:
 float operator ()(ComplexNetwork< shared_ptr<const FeatureAbstract>, Link> *cn, node_id from, node_id to){
    return cn->getEdge(from, to)->getWeight();
 }
};

int main1(int argc, char* argv[]){
    /*QList<FeatureFactoryAbstract*> factories;
    LabelFeatureFactory label;
    factories.append(&label);

    FeaturesComplexNetwork rc;
    rc.load("/tmp/Implementation-Build/bin/labelsNetwork.cn",factories);

    int i=0;
    for(FeaturesComplexNetwork::EdgeIterator edge=rc.EdgesBegin(); edge!=rc.EdgesEnd(); edge++){
        printf("%d %d\n",i++, rc.getNumEdges());
        //printf("%d %d -> %f\n", edge.getFromNodeId(), edge.getToNodeId(), edge->getWeight());
    }
    assert(i==rc.getNumEdges());

    typedef CachedComplexNetwork<int, float> net;
    net cn(true);
    cn.addNode(1);
    cn.addNode(2);
    cn.addNode(3);
    cn.addNode(4);

    cn.addEdge(cn.getNodeId(1), cn.getNodeId(2), 0.8);
    cn.addEdge(cn.getNodeId(1), cn.getNodeId(3), 0.2);
    cn.addEdge(cn.getNodeId(3), cn.getNodeId(2), 0.8);
    cn.addEdge(cn.getNodeId(3), cn.getNodeId(4), 0.2);

    */
    QList<FeatureFactoryAbstract*> features;
    LabelFeatureFactory label;
    features.append(&label);
    FeaturesComplexNetwork cn;
    cn.load("/tmp/Implementation-Build/bin/labels_sem_rep.cn", features);

    FeaturesComplexNetwork::NodeIterator nodes;
    FeaturesComplexNetwork::EdgeIterator edges;
    for( nodes = cn.Begin(); nodes != cn.End(); nodes++){
        //sum weights
        double weight = 0.0;
        for( edges = nodes.EdgesBegin(); edges != nodes.EdgesEnd(); edges++ ){
                weight += edges->getWeight();
        }
        for( edges = nodes.EdgesBegin(); edges != nodes.EdgesEnd(); edges++ ){
                edges->setWeight(edges->getWeight()/weight);
        }
    }
/*
    printf("Carregado e normalizado\n");
    BreadFirstRandomWalk<shared_ptr<const FeatureAbstract>, Link, getWeight> dij(&cn);
    printf("%d\n", cn.getNumNodes());
    char buffer[100];
    //for(int i=0;i<cn.getNumNodes();i++){
    //    printf("%d - no escolhido %s\n", i , cn.getNode(i)->get()->asString(buffer));
    //    fflush(stdout);
    //}

    node_id escolhido = 0;
    printf(" %d - no escolhido %s\n", escolhido , cn.getNode(escolhido)->get()->asString(buffer));
    fflush(stdout);
    dij.Execute(escolhido, 100);
    QList<node_id> nodes_ordered;
    for(int i=0;i<cn.getNumNodes();i++){
        if(dij.getProbability(i) > 0.00001){
            nodes_ordered.append(i);
        }
    }
    qSort(nodes_ordered.begin(), nodes_ordered.end(), [&](const node_id& a, const node_id&b){return dij.getProbability(a) > dij.getProbability(b);});
    for(int i=0;i<min(10, nodes_ordered.size());i++){
        printf("%-30s = %f %%\n", cn.getNode(nodes_ordered[i])->get()->asString(buffer), dij.getProbability(nodes_ordered[i]));
        //Link *f = cn.getEdge(escolhido, nodes_ordered[i]);
        //printf("%s = %f %%\n", cn.getNode(nodes_ordered[i])->get()->asString(buffer), f ? f->getWeight() : -1);
    }*/

    return 0;
}


int main(int argc, char* argv[]){

    char buffer[100];
    QList<FeatureFactoryAbstract*> features;
    LabelFeatureFactory label;
    features.append(&label);
    FeaturesComplexNetwork cn;
    cn.load("/tmp/Implementation-Build/bin/labels_sem_rep.cn", features);

    FeaturesComplexNetwork::NodeIterator nodes;
    FeaturesComplexNetwork::EdgeIterator edges;
    for( nodes = cn.Begin(); nodes != cn.End(); nodes++){
        //sum weights
        double weight = 0.0;
        for( edges = nodes.EdgesBegin(); edges != nodes.EdgesEnd(); edges++ ){
                weight += edges->getWeight();
        }
        for( edges = nodes.EdgesBegin(); edges != nodes.EdgesEnd(); edges++ ){
                edges->setWeight(edges->getWeight()/weight);
        }
    }
    /*
    printf("Carregado e normalizado\n");
    IterativeRandomWalk<shared_ptr<const FeatureAbstract>, Link, getWeight> dij(&cn);
    dij.Execute(0, 10);
    QList<node_id> nodes_ordered;
    for(int i=0;i<cn.getNumNodes();i++){
        if(dij.getProbability(i) > 0.00001){
            nodes_ordered.append(i);
        }
    }
    qSort(nodes_ordered.begin(), nodes_ordered.end(), [&](const node_id& a, const node_id&b){return dij.getProbability(a) > dij.getProbability(b);});
    for(int i=0;i<min(10, nodes_ordered.size());i++){
        printf("%-30s = %f %%\n", cn.getNode(nodes_ordered[i])->get()->asString(buffer), dij.getProbability(nodes_ordered[i]));
        //Link *f = cn.getEdge(escolhido, nodes_ordered[i]);
        //printf("%s = %f %%\n", cn.getNode(nodes_ordered[i])->get()->asString(buffer), f ? f->getWeight() : -1);
    }*/
    return 0;
}


