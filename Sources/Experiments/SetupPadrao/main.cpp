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


int main(int argc, char **argv) {
    //QCoreApplication app(argc, argv);
    FeaturesComplexNetwork cn;
    FeaturesComplexNetwork cn2;

    QList<const FeatureFactoryAbstract*> features;
    features.append(new LabelFeatureFactory());
    features.append(new  HsvFeatureFactory(18,3,3,5) );
    features.append(new  OrientationFeatureFactory(18) );
    features.append(new  AreaFeatureFactory(18) );
    /*
    {
        tictac::tic();
        SunDatabaseReader reader("/Users/wachs/SUN/");
        ComplexNetworkConstructor builder(cn, reader, features, NULL);
        builder.build();
        cn.save("teste.train");
        tictac::tac();
    }
     */
    {
        tictac::tic();
        FeaturesComplexNetwork cnTemp;
        SunDatabaseReader reader(argv[1]);
        ComplexNetworkConstructorP builderP(cnTemp, reader, features, NULL);
        builderP.build();
        puts("terminei");
        fflush(stdout);
        cnTemp.save("saida.train");
        tictac::tac();
    }
    //cn.load("teste.train", features);
    /*
    cn2.load("teste2.train", features);
    printf("Nos: %d - Arestas: %d\n", cn.getNumNodes(), cn.getNumArcs());
    printf("Nos: %d - Arestas: %d\n", cn2.getNumNodes(), cn2.getNumArcs());
    float sum=0;
    char buffer[50];

    for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it ) {
        for(FeaturesComplexNetwork::NodeIt it2(cn); it2 != INVALID; ++it2 ) {
            FeatureAbstractPtr &node = cn.getNode(it);
            FeatureAbstractPtr &node2 = cn.getNode(it2);
            if(cn.arcExists(it,it2)) {

                auto v1 = cn.getArcValue(cn.getNodeFromFeature(node), cn.getNodeFromFeature(node2)).getWeight();
                auto v2 = cn2.getArcValue(cn2.getNodeFromFeature(node), cn2.getNodeFromFeature(node2)).getWeight();
                sum += v2-v1;
            }
        }
    }
    printf("soma = %f\n", sum);
     //return app.exec();*/
    return 0;
}



