
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

    QList<FeatureFactoryAbstract*> feat;
    LabelFeatureFactory label;
    feat.append(&label);

    FeaturesComplexNetwork net;
    net.load("/tmp/Implementation-Build/bin/labelsNetwork.cn", feat);

    CachedComplexNetwork<int, double> net2(true);
    net2 = RandomWalk::convertToWalkNetwork(net);

    CachedComplexNetwork<int, double> net3;
    net3 = RandomWalk::normalizeGraph(net2);
    net3 = RandomWalk::walkOneStep(net3);
    printf("%.2f\n", *net2.getEdge(net2.getNodeId(1), net2.getNodeId(3)));
    printf("%.2f\n", *net3.getEdge(net3.getNodeId(1), net3.getNodeId(3)));

    float w = 0;
    for(auto n = net3.EdgesBegin(net3.getNodeId(1)); n != net3.EdgesEnd(net3.getNodeId(1)); n++){
        printf("%d->%.2f\n", *net3.getNode(n.getToNodeId()), *n );
        w += *n;
    }
    printf("%.2f\n", w);


/*
    SunDatabaseReader reader("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/Sun1/");
    while(reader.hasNext()){
        SupervisedImage i = reader.readNext();
        //cv::Mat m = i.getRegions()[0].getMask();
        cv::Mat m = i.getRegions()[0].getCvImage();
        cv::imshow("img", m);
        cv::waitKey();
    }
*/
    return 0;
}
