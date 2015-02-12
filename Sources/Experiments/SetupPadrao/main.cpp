#include <stdio.h>
#include <stdlib.h>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/GraphUtilities.hpp>
#include <Utilities/IterativeRandomWalk.hpp>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <QList>

#include <QHash>
int main(int argc, char* argv[]){
    typedef FeaturesComplexNetwork CN;
    CN c;
    QList<FeatureFactoryAbstract*> factories;
    AreaFeatureFactory area(10);
    LabelFeatureFactory label;
    OrientationFeatureFactory orientation(10);

    factories.append(&label);

    c.load("complex_network.cn", factories);
    printf("carreguei\n");
    fflush(stdout);

    CN::ArcMap<double> weights(c);

    GraphUtilities::getWeights(c, weights);
    IterativeRandomWalk walk(c, weights);

    walk.Execute(c.nodeFromId(1000), 3);
    double p = 0;
    for(FeaturesComplexNetwork::NodeIt it(c); it != INVALID; ++it ){
        p  += walk.getProbability(it);
        printf("%f\n", walk.getProbability(it));
    }
    printf("%f\n", p);

    return 0;
}
