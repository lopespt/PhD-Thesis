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

    typedef FeaturesComplexNetwork::Node Node;

    FeaturesComplexNetwork::NodeMap<double> degs(cn);
    FeaturesComplexNetwork::ArcMap<double> weights(cn);
    GraphUtilities::getWeights(cn, weights);
    Degrees::computeDegreeMap(cn,  weights, degs);

    QList<FeaturesComplexNetwork::Node> list;
    for(FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it){
        list.append(it);
    }

    qSort(list.begin(), list.end(), [&](const Node& a, const Node& b){
        return degs[a] > degs[b];
    });

    char buffer[50];
    for(const Node &t: list){
        if(cn.getNode(t)->getType() == 0 ) {
            printf("%-40s %f\n", cn.getNode(t)->asString(buffer), degs[t] );
        }
    }

    tic();
    MCLClustering m(cn, weights);
    m.execute();
    tac();

    tic();
    Modularity modularity(cn, m.getClustersMap());
    float mod = modularity.executeP(8);
    printf("%f", mod);
    tac();


    FILE *f = fopen("clusters.txt","w");
    for(int i=0;i < m.getTotalClusters(); i++){
        fprintf(f,"Cluster %d:\n", i+1);
        auto nodes = m.getClusterNodes(i);
        for(Node node: nodes) {
            fprintf(f, "%s\n", cn.getNode(node)->asString(buffer));
        }
    }

    fclose(f);



    return 0;
}



