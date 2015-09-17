#include <QCoreApplication>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <QCommandLineParser>
#include <Utilities/tictac.h>
#include "../LabelGuesser/ConfigParser.h"
#include "LabelGuesserExperimentRemovingHints.hpp"
#include <QStringList>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructorP.hpp>
#include <Utilities/DatabaseReader/RegionChooser.hpp>
#include <Utilities/ClusteringCoefficient.h>
#include <Utilities/GraphUtilities.hpp>
#include <lemon/dijkstra.h>

void createFiles(ConfigParser &config) {
    FeaturesComplexNetwork cn;
    SunDatabaseReader reader(config.getDatabasePath());

    KFoldDatabaseReader kfold(reader, config.getKFoldTrainPercentage());

    kfold.save(config.getKFoldFilePath());

    KFoldDatabaseReader::PathDatabaseReader testSet = kfold.getTestReader();

    RegionChooser chooser(testSet);
    chooser.save(config.getChoosenRegionFilePath());

}

void buildCN(ConfigParser &config ){
    FeaturesComplexNetwork cn;
    QList<const FeatureFactoryAbstract *> factories = config.getFactories();
    KFoldDatabaseReader kfold(config.getKFoldFilePath());

    KFoldDatabaseReader::PathDatabaseReader trainSet = kfold.getTrainReader();

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
    srand(time(NULL));


    bool constructor_enabled = config.hasToBuildCN();

    bool guesser_execute = !config.getGuesserOutput().isEmpty();
    QString guesser_output = config.getGuesserOutput();
    int walk_length = config.getPreferedValue("label_guesser_experiment/walk_length","","1").toInt();
    LabelGuesserExperimentRemovingHints::method method;
    int numThreads = config.getNumThreads();
    printf("%d\n", config.getFactories().size());


    QStringList vals;
    vals << "xor" << "mult" << "add";
    switch (vals.indexOf(config.getPreferedValue("label_guesser_experiment/method","", "xor"))) {
        case 0:
            method = LabelGuesserExperimentRemovingHints::XorProbabilities;
            break;
        case 1:
            method = LabelGuesserExperimentRemovingHints::MultProbabilities;
            break;
        case 2:
            method = LabelGuesserExperimentRemovingHints::SumProbabilities;
            break;
        default:
            warn("Erro: não foi possivel encontrar um metodo para guesser utilizando default XOR\n");
            method = LabelGuesserExperimentRemovingHints::XorProbabilities;
    }


    if(!QFile::exists(config.getKFoldFilePath()) || !QFile::exists(config.getChoosenRegionFilePath())){
        createFiles(config);
    }


    FeaturesComplexNetwork cn;
    if(constructor_enabled){
        buildCN(config);
        cn.load(config.getCnOutput().toStdString().c_str(), config.getFactories());
    }else if (!config.getCnInput().isEmpty()){
        cn.load(config.getCnInput().toStdString().c_str(), config.getFactories());
    }else{
        puts("No Complex Network to work!! Exiting");
        return 0;
    }


    RegionChooser region_chooser(config.getChoosenRegionFilePath());

    if(guesser_execute){
        float percArray[]={1.0, 0.25, 0.5, 0.75, 1};
        //float percArray[]={1.0};
        for(const double percentageHints : percArray ) {
            LabelGuesserExperimentRemovingHints l1(cn, config.getFactories(), region_chooser, walk_length, method,
                                                   numThreads,
                                                   percentageHints);
            printf("Iniciando experimento eliminando %.0f%% de Hints\n", percentageHints*100);
            QString goutput(guesser_output);
            goutput.replace(".",QString("%1.").arg(percentageHints));
            l1.execute(goutput);
            printf("Terminado\n");
        }
    }
    tac();

    return 0;
}
