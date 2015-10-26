#include <stdio.h>
#include <stdlib.h>
#include <ComplexNetwork/ComplexNetwork.hpp>

#include <Utilities/tictac.h>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <Utilities/MCLClustering.hpp>
#include <Utilities/Modularity.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <Experiments/PhysicalMeasures/Measures/DegreeDistribution.hpp>
#include <qfile.h>
#include <qtextstream.h>
#include <Experiments/PhysicalMeasures/Measures/WeightDistribution.hpp>
#include <Experiments/PhysicalMeasures/Measures/DistanceDistribution.hpp>

using namespace tictac;
using namespace std;

#include "Measures/ClusteringCoefficient.hpp"

void gravaDist(const FeaturesComplexNetwork &cn, const DegreeDistribution::NodeMap &dist, QString filename){
    FILE * f = fopen(filename.toStdString().c_str(),"w");
    for( FeaturesComplexNetwork::NodeIt it(cn); it != INVALID; ++it ){
        fprintf(f, "%-20.5f\n", dist[it]);
    }
    fclose(f);
}
void gravaDist(const FeaturesComplexNetwork &cn, const WeightDistribution::ArcMap &dist, QString filename){
    FILE * f = fopen(filename.toStdString().c_str(),"w");
    for( FeaturesComplexNetwork::ArcIt it(cn); it != INVALID; ++it ){
        fprintf(f, "%-20.5f\n", dist[it]);
    }
    fclose(f);
}

int main(int argc, char **argv) {

    puts("Carregando");
    FeaturesComplexNetwork cn;
    QList<const FeatureFactoryAbstract *> factories;
    HsvFeatureFactory hsv(10,3,6,3);
    LabelFeatureFactory label;
    AreaFeatureFactory area(5);
    OrientationFeatureFactory orie(5);
    factories.append(&hsv);
    factories.append(&label);
    factories.append(&area);
    factories.append(&orie);

    cn.load("/tmp/F_3/H10_S3_V6/A_5/O_5/network.cn",factories);
    puts("Pronto!");

    //float result = ClusteringCoefficient::Compute(cn, 5, 0.5);

    //printf("%f\n", result);

    /*
    DegreeDistribution dist(cn);
    dist.run();
    WeightDistribution wdist(cn);
    wdist.run();

    gravaDist(cn, dist.getInDegrees(), "in.txt");
    gravaDist(cn, dist.getOutDegrees(), "out.txt");
    gravaDist(cn, dist.getSumInDegrees(), "sumin.txt");
    gravaDist(cn, dist.getSumOutDegrees(), "sumout.txt");
    gravaDist(cn, wdist.getWeightsDistribution(), "weights.txt");
    */

    DistanceDistribution dist(cn);
    dist.run();



    printf("Fim\n");

    return 0;
}



