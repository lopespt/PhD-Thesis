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
        QList<const FeatureFactoryAbstract *> factories;
        LabelFeatureFactory lblFactory;
        factories.append(&lblFactory);
        {

        FeaturesComplexNetwork cn1;
        SunDatabaseReader reader("/Users/wachs/SUN/");
        ComplexNetworkConstructorP constr(cn1, reader, factories, 8);
        constr.build();
        cn1.save("rede1.cn");
        }

        FeaturesComplexNetwork cn1;
        cn1.load("rede1.cn",factories);
        FeaturesComplexNetwork cn2;
        cn2.load("rede1.cn", factories);

        int i=0;
        for(FeaturesComplexNetwork::ArcIt it(cn1); it != INVALID; ++it){
                FeatureAbstractPtr f1,f2;
                f1 = cn1.getNode( cn1.source(it) );
                f2 = cn1.getNode( cn1.target(it) );

                float w = cn1.getLinkArcValue(it).getWeight();
                float w2 = cn2.getLinkArcValue(cn2.getNodeFromFeature(f1), cn2.getNodeFromFeature(f2)).getWeight();
                if(w!=w2){
                    exit(11);
                }
            printf("%d\n", ++i);
        }
        puts("Ok!!");

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

