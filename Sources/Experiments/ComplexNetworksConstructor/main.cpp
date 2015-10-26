#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <Utilities/FeaturesComplexNetwork/Link.hpp>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <qcoreapplication.h>
#include <Utilities/ConfigParser.h>
#include <Experiments/LabelGuesser/LabelGuesserExperiment.hpp>
#include <Utilities/tictac.h>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructorP.hpp>
#include <Utilities/GraphUtilities.hpp>

void createFiles(ConfigParser &config) {
    FeaturesComplexNetwork cn;
    SunDatabaseReader reader(config.getDatabasePath());

    KFoldDatabaseReader kfold(reader, config.getKFoldTrainPercentage());

    kfold.save(config.getKFoldFilePath());

    KFoldDatabaseReader::PathDatabaseReader testSet = kfold.getTestReader();

    RegionChooser chooser(testSet);
    chooser.save(config.getChoosenRegionFilePath());

}

void buildCN(FeaturesComplexNetwork &cn, ConfigParser &config ){
    QList<const FeatureFactoryAbstract *> factories = config.getFactories();
    //KFoldDatabaseReader kfold(config.getKFoldFilePath());

    //KFoldDatabaseReader::PathDatabaseReader trainSet = kfold.getTrainReader();
    SunDatabaseReader trainSet(config.getDatabasePath());

    if(config.getNumThreads() <= 1) {
        ComplexNetworkConstructor constructor(cn, trainSet, factories);
        constructor.build();
    }else{
        ComplexNetworkConstructorP constructor(cn, trainSet, factories, config.getNumThreads());
        constructor.build();
    }
    cn.refreshCache();
    cn.save(config.getCnOutput().toStdString().c_str());
}

using namespace tictac;

int main(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);
    ConfigParser config(app);
    tic();

    bool constructor_enabled = config.hasToBuildCN();
    int numThreads = config.getNumThreads();
    printf("Number of factories: %d\n", config.getFactories().size());

/*    if (!QFile::exists(config.getKFoldFilePath()) || !QFile::exists(config.getChoosenRegionFilePath())) {
        createFiles(config);
    }
*/
    FeaturesComplexNetwork cn;
    buildCN(cn, config);


    tac();
    return 0;


}
