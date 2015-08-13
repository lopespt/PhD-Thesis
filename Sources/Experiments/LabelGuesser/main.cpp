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
#include <QStringList>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructorP.hpp>

void createFiles() {
    FeaturesComplexNetwork cn;
    SunDatabaseReader reader("/Users/wachs/SUN");

    KFoldDatabaseReader kfold(reader, 0.7);
    kfold.save("images_set.kfold");

    KFoldDatabaseReader::PathDatabaseReader testSet = kfold.getTestReader();
    KFoldDatabaseReader::PathDatabaseReader trainSet = kfold.getTrainReader();


    QList<const FeatureFactoryAbstract *> factories;
    LabelFeatureFactory l;
    HsvFeatureFactory hsv(4, 3, 3, 20);
    factories.append(&l);
    //   factories.append(&hsv);

    ComplexNetworkConstructor constructor(cn, trainSet, factories);
    constructor.build();
    cn.refreshCache();
    cn.save("train_labels.cn");
    RegionChooser chooser(testSet);
    chooser.save("chosenRegions.txt");
}

int main2(int argc, char *argv[]) {

    QCoreApplication app(argc, argv);

    createFiles();

    FeaturesComplexNetwork cn;

    QList<const FeatureFactoryAbstract *> factories;
    LabelFeatureFactory l;
    HsvFeatureFactory hsv(4, 3, 3, 20);
    factories.append(&l);
    factories.append(&hsv);
    cn.load("/tmp/Implementation-Build/bin/train_labels.cn", factories);

    RegionChooser chooser("/tmp/Implementation-Build/bin/chosenRegions.txt");
    printf("Iniciando experimentos\n");
    return 0;
}
using namespace tictac;
int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addOption(QCommandLineOption(QStringList() << "threads" << "j","Number of threads for construction", "Threads","1"));
    parser.process(app);
    tic();

    ConfigFileParser config(argv[1]);
    FeaturesComplexNetwork cn = config.getComplexNetwork();
    bool constructor_enabled = config.getValue("constructor_general/constructor_enabled").toBool();
    bool constructor_save = config.getValue("constructor_general/save").toBool();
    bool guesser_execute = config.getValue("label_guesser_experiment/execute").toBool();
    QString guesser_output = config.getValue("label_guesser_experiment/output_file").toString();
    int walk_length = config.getValue("label_guesser_experiment/walk_length").toInt();
    LabelGuesserExperiment::method method;
    bool useLabels = config.getValue("label_guesser_experiment/use_labels", true).toBool();
    int numThreads = parser.value("threads").toInt();

    QStringList vals;
    vals << "xor" << "mult" << "add";
    switch (vals.indexOf(config.getValue("label_guesser_experiment/method").toString())) {
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

    if (!config.cnLoaded()) {
        if(numThreads > 1) {
            ComplexNetworkConstructorP constructor = config.getConstructorP(cn, numThreads);
            if (constructor_enabled) {
                constructor.build();
                if (constructor_save)
                    cn.save(config.getValue("FeaturesComplexNetwork/file").toString().toStdString().c_str());
            }
        }else{
            ComplexNetworkConstructor constructor = config.getConstructor(cn);
            if (constructor_enabled) {
                constructor.build();
                if (constructor_save)
                    cn.save(config.getValue("FeaturesComplexNetwork/file").toString().toStdString().c_str());
            }
        }
    }
    RegionChooser region_chooser = config.getRegionChooser();

    if (guesser_execute) {
        LabelGuesserExperiment l1(cn, config.getFactories(), region_chooser, walk_length, method,numThreads, useLabels);
        printf("Iniciando experimento\n");
        l1.execute(guesser_output);
        printf("Terminado\n");
        tac();
    }

    return 0;
}
