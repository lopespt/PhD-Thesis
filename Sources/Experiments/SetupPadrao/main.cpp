#include <stdio.h>
#include <stdlib.h>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/GraphUtilities.hpp>
#include <Utilities/IterativeRandomWalk.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <QCoreApplication>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructorP.hpp>
#include <FeatureExtractors/LabelFeature.hpp>

using namespace cv;
using namespace std;
#include <Utilities/tictac.h>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <Utilities/MCLClustering.hpp>
#include <Utilities/Modularity.hpp>

using namespace tictac;
int main(int argc, char **argv) {
    FeaturesComplexNetwork cn;
    QList<const FeatureFactoryAbstract*> factories;
    factories.append(new LabelFeatureFactory());
    factories.append(new HsvFeatureFactory(20,3,6,8));

    tic();
    cn.load("train20_3_6_8.cn", factories);
    tac();

    FeaturesComplexNetwork::ArcMap<double> l(cn);
    GraphUtilities::getWeights(cn, l);

    tic();
    MCLClustering m(cn, l);
    m.execute();
    tac();

    /*
    char buff[200];
    QList<FeaturesComplexNetwork::Node> nd = m.getClusterNodes(0);
    for( FeaturesComplexNetwork::Node& n : nd ){
        cn.getNode(n)->asString(buff);
        printf("%s ", buff);
    }
    printf("%d\n", m.getTotalClusters());
*/
    tic();
    Modularity modularity(cn, m.getClustersMap());
    float mod = modularity.executeP(8);
    printf("%f", mod);
    tac();




    return 0;
}



