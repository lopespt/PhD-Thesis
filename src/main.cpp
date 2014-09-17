#include <stdio.h>
#include <QCoreApplication>
#include "ComplexNetwork.hpp"


int main(int argc, char **argv){

    QCoreApplication a(argc, argv);
    printf("teste\n");

    ComplexNetwork< const int , float> net;
    Node<const int, float> *n1 = new Node<const int, float>(1);
    Node<const int, float> *n2 = new Node<const int, float>(2);
    Node<const int, float> *n3 = new Node<const int, float>(3);
    net.addNode(n1);
    net.addNode(n2);
    net.addNode(n3);

    Edge<const int, float> *e = new Edge<const int, float>(n1, n2, 555);
    Edge<const int, float> *e2 = new Edge<const int, float>(n1, n3, 1000);
    net.addEdge(e);
    net.addEdge(e2);
    

    Edge<const int, float>* l = net.getEdge(net.getNode(1)  , net.getNode(2));

    auto aa = net.getEdgesFromNode_LowerBound(net.getNode(3));
    auto aa2 = net.getEdgesFromNode_UpperBound(net.getNode(3));

    for(auto i=aa; i!=aa2; i++){
        printf("%f", i->second->getAttribute());
    }

    if(net.getNode(1) != NULL){
        //printf( "%ld", (long ) net.getNode(1));
    }else{
        printf("NULL");
    }

    //printf("%f", l->getAttribute());


    //delete n;
    
//    return a.exec();
    return 0;
}
