#include "LabelGuesserExperiment.hpp"
#include <QCoreApplication>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include "ConfigFileParser.hpp"
#include <QCommandLineParser>
#include <Utilities/tictac.h>
#include "ConfigParser.h"
#include <QStringList>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructorP.hpp>

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




    bool constructor_enabled = config.hasToBuildCN();
    printf("%d\n\n", constructor_enabled);
    bool constructor_save = !config.getCnOutput().isEmpty();
    bool guesser_execute = true;
    QString guesser_output = config.getGuesserOutput();
    int walk_length = config.getPreferedValue("label_guesser_experiment/walk_length","","1").toInt();
    LabelGuesserExperiment::method method;
    bool useLabels = true;
    int numThreads = config.getNumThreads();


    QStringList vals;
    vals << "xor" << "mult" << "add";
    switch (vals.indexOf(config.getPreferedValue("label_guesser_experiment/method","", "xor"))) {
        case 0:
            method = LabelGuesserExperiment::XorProbabilities;
            break;
        case 1:
            method = LabelGuesserExperiment::MultProbabilities;
            break;
        case 2:
            method = LabelGuesserExperiment::SumProbabilities;
            break;
        default:
            warn("Erro: não foi possivel encontrar um metodo para guesser utilizando default XOR\n");
            method = LabelGuesserExperiment::XorProbabilities;
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

    LabelGuesserExperiment l1(cn, config.getFactories(), region_chooser, walk_length, method,numThreads, useLabels);
    printf("Iniciando experimento\n");
    l1.execute(guesser_output);
    printf("Terminado\n");
    tac();

    return 0;
}
