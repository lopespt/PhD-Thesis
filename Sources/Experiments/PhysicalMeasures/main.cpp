#include <stdio.h>
#include <stdlib.h>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <set>
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
#include <Utilities/ConfigParser.h>
#include <Utilities/fiboqueue.h>

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



template<typename K, typename V>
class Keyer{
public:
    K key;
    V value;
    bool operator<(const Keyer& b) const {
        return this->key < b.key;
    }

    bool operator>(const Keyer& b) const {
        return this->key > b.key;
    }

    bool operator==(const Keyer& b)const {
        return this->key == b.key;
    }

    Keyer operator-(const Keyer& b) const{
        return  {this->key, this->value-b.value};
    }
};

/*template <typename K, typename V>
struct std::hash<Keyer<K,V> >{
    size_t operator()(const Keyer<K,V>& obj) const{
        return std::hash<K>()(obj.key);
    };
};*/



int main(int argc, char **argv) {
    puts("v6");
    QCoreApplication app(argc, argv);
    ConfigParser config(app);


    puts("Carregando");
    FeaturesComplexNetwork cn;
    cn.load(config.getCnInput().toStdString().c_str(), config.getFactories());
    puts("Pronto!");

    //ClusteringCoefficient CC(cn, config.getNumThreads(), 0.5);
    //float result = CC.Compute();
    //printf("CC = %f\n", result);

    //printf("%f\n", result);

    /*DegreeDistribution dist(cn);
    dist.run();
    WeightDistribution wdist(cn);
    wdist.run();

    gravaDist(cn, dist.getInDegrees(), "in.txt");
    gravaDist(cn, dist.getOutDegrees(), "out.txt");
    gravaDist(cn, dist.getSumInDegrees(), "sumin.txt");
    gravaDist(cn, dist.getSumOutDegrees(), "sumout.txt");
    gravaDist(cn, wdist.getWeightsDistribution(), "weights.txt");*/

    DistanceDistribution dist(cn, config.getNumThreads(), config.getCnOutput().toStdString().c_str());
    dist.run();
    //gravaDistancias(cn, dist.getDist(), config.getCnOutput());

    /*FeaturesComplexNetwork::ArcMap<double> weights(cn);
    GraphUtilities::getWeights(cn,weights);
    MCLClustering mod(cn,weights);
    mod.execute();*/
    printf("Fim\n");

    return 0;
}

//CC = 0.050027


