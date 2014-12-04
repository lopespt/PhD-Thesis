
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

    FeaturesComplexNetwork net2;
    net2 = net;
    printf("%f\n",net2.getEdge(10 , 100)->getWeight());

    //RandomWalk::normalizeGraph(net);



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
