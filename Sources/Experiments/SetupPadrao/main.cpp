
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <FeatureExtractors/Region.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/RandomWalk.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <QList>
int main(int argc, char* argv[]){

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
*/
    for(int i=0;i<10;i++){
    typedef CachedComplexNetwork<int, float> net;
    net cn;
    for(int k=0;k<1000;k++){
        cn.addNode(k);
    }

    for(int k=0;k<10000;k++){
        cn.addEdge(rand()%999, rand()%999, 1.2);
    }
        int j=0;
        for(net::EdgeIterator edge = cn.EdgesBegin(); edge != cn.EdgesEnd(); edge++){
            j++;
        }
        printf("%d==%d\n", j, cn.getNumEdges());
        assert(j==cn.getNumEdges());
        printf("ok\n");
    }

    return 0;
}
