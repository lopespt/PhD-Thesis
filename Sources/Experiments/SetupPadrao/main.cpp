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
#include <Utilities/Modularity.hpp>


int main(int argc, char **argv) {
    FeaturesComplexNetwork cn;
    QList<const FeatureFactoryAbstract*> factories;
    factories.append(new LabelFeatureFactory());
    factories.append(new HsvFeatureFactory(20,9,6,4));
    cn.load("train20_9_6_4.cn", factories);


    FeaturesComplexNetwork::ArcMap<double> l(cn);
    GraphUtilities::getWeights(cn, l);

    Modularity m(cn, l);
    m.execute();

    return 0;
}



