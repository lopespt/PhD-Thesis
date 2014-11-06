
#include <Utilities/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/AreaFeatureExtractor.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <FeatureExtractors/Feature.hpp>
#include <Utilities/Link.hpp>
#include <QList>

int main(int argc, char* argv[]){

    SunDatabaseReader reader("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial");

    ComplexNetwork<FeatureAbstract, Link> cn;
    AreaFeatureExtractor area(5);
    QList<FeatureExtractorAbstract*> features;
    features.append(&area);
    ComplexNetworkConstructor constructor(cn, reader, features);
    constructor.build();

    cn.save("areas.cn");


    return 0;
}
