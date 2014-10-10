#include "LabelsComplexNetworkConstructor.hpp"


LabelsComplexNetworkConstructor::LabelsComplexNetworkConstructor(ComplexNetwork<NodeString, Link>& cn, DatabaseReader &reader):cn(cn), reader(reader)
{

}

void LabelsComplexNetworkConstructor::build(){

    while(reader.hasNext()){
        SupervisedImage i = reader.readNext();
        Node<NodeString, Link>* n1, *n2;
        Edge<NodeString, Link>* e;
        link_time t=0;

        foreach(Region* r1, i.getRegions()){
            foreach(Region* r2, i.getRegions()){

                QString label1 = r1->getLabel();
                QString label2 = r2->getLabel();

                if( (n1 = cn.getNode(label1)) == NULL){
                    n1=new Node<NodeString, Link>(label1);
                    cn.addNode(n1);
                }
                if( (n2 = cn.getNode(label2)) == NULL){
                    n2=new Node<NodeString, Link>(label2);
                    cn.addNode(n2);
                 }

                if(n1 != n2){
                    if( (e = cn.getEdge(n1, n2)) == NULL){
                        e = new Edge<NodeString, Link>(n1,n2, Link(t,1));
                        cn.addEdge(e);
                    }else{
                        Link l = e->getAttribute();
                        l.setTime(t++);
                        l.setWeight(l.getWeight()+1);
                        e->setAttribute(l);
                    }
                }
            }
        }
    }
}
