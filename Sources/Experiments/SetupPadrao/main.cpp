#include <stdio.h>
#include <stdlib.h>
#include <opencv2/core/core.hpp>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <FeatureExtractors/LabelFeature.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

    FeaturesComplexNetwork cn;

    FeatureAbstractPtr n1(new LabelFeature("Teste"));
    FeatureAbstractPtr n2(new LabelFeature("Teste 1"));
    FeatureAbstractPtr n3(new LabelFeature("Teste 2"));
    FeatureAbstractPtr n4(new LabelFeature("Teste"));
    FeatureAbstractPtr n5(new LabelFeature("Teste 2"));

    cn.addNode(n1);
    cn.addNode(n2);
    cn.addNode(n3);
    Link l(5,3, Link::LinkType::SameLabel);
    cn.addArc( cn.getNodeFromFeature(n4), cn.getNodeFromFeature(n5), l );
    float f = cn.getLinkArcValue( cn.getNodeFromFeature(n4) , cn.getNodeFromFeature(n5), Link::LinkType::SameLabel).getWeight();

    printf("%f\n", cn.getLinkArcValue( cn.getNodeFromFeature(n1) , cn.getNodeFromFeature(n3), Link::LinkType::SameLabel).getWeight()   );
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

