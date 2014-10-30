
#include <Utilities/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/AreaFeatureExtractor.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <FeatureExtractors/Feature.hpp>
#include <Utilities/Link.hpp>
#include <QList>

int main(int argc, char* argv[]){

    SunDatabaseReader reader("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial");

    ComplexNetwork<Feature, Link> cn;
    int discretization = 5;
    AreaFeatureExtractor area(&discretization);
    QList<FeatureExtractor*> features;
    features.append(&area);
    ComplexNetworkConstructor constructor(cn, reader, features);
    constructor.build();

    cn.save("areas.cn");


    return 0;
}
