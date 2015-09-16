#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

    FeaturesComplexNetwork cn;

    Link l;
    l.setLinkType( (Link::LinkType) 2);
    printf("%d\n", l.type);

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

