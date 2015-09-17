#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <FeatureExtractors/LabelFeature.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructorP.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

    {
        FeaturesComplexNetwork cn;
        SunDatabaseReader reader("/Users/wachs/SUN");
        LabelFeatureFactory lblFactory;
        HsvFeatureFactory hsvFactory(10,4,4,4);
        QList<const FeatureFactoryAbstract *> factories;
        factories << &lblFactory << &hsvFactory;

        ComplexNetworkConstructorP constructor(cn, reader, factories, 8);
        constructor.build();
        cn.save("rede3.cn");
    }
    return 0;
}

/*
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
    tic();
    Modularity modularity(cn, m.getClustersMap());
    float mod = modularity.executeP(8);
    printf("%f", mod);
    tac();




    return 0;
}


 */

