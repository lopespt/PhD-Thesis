#include "LabelsComplexNetworkConstructor.hpp"


LabelsComplexNetworkConstructor::LabelsComplexNetworkConstructor(ComplexNetwork<NodeString, Link>& cn, DatabaseReader &reader):cn(cn), reader(reader)
{

}

void LabelsComplexNetworkConstructor::build(){

    int counter=1;
    while(reader.hasNext() ){
        try{
            SupervisedImage i = reader.readNext();
            printf("Reading image(%d/%d): %s%s\n", counter, reader.getTotal(), i.getImagePath().size()>60?"...":"",i.getImagePath().right(60).toStdString().c_str());
            Node<NodeString, Link>* n1, *n2;
            Edge<NodeString, Link>* e;
            link_time t=0;

            //foreach(Region r1, i.getRegions()){
            //foreach(Region r2, i.getRegions()){
            for(QList<Region>::const_iterator it1=i.getRegions().begin(); it1!=i.getRegions().end(); it1++){
                for(QList<Region>::const_iterator it2=it1+1; it2!=i.getRegions().end(); it2++){
                    Region r1 = *it1;
                    Region r2 = *it2;
                    QString label1 = r1.getLabel();
                    QString label2 = r2.getLabel();

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
        }catch(exception e){
            printf("Exception occurred: %s\n", e.what());
            fflush(stdout);
        }
        counter++;
    }
}
