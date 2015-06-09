#include "LabelGuesserExperiment.hpp"
#include <QCoreApplication>
#include "LabelGuesserExperimentThread.hpp"
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include "ConfigFileParser.hpp"
#include <QCommandLineParser>

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
    return 0;

    FeaturesComplexNetwork cn;

    QList<const FeatureFactoryAbstract *> factories;
    LabelFeatureFactory l;
    HsvFeatureFactory hsv(4, 3, 3, 20);
    factories.append(&l);
    factories.append(&hsv);
    cn.load("/tmp/Implementation-Build/bin/train_labels.cn", factories);

    RegionChooser chooser("/tmp/Implementation-Build/bin/chosenRegions.txt");
    printf("Iniciando experimentos\n");

    LabelGuesserExperimentThread l1(cn, factories, chooser, 3, LabelGuesserExperiment::XorProbabilities,
                                    "/Users/wachs/SUN/", "guess_reinf_70p_1w_Xor.txt");
    l1.start();

    LabelGuesserExperimentThread l2(cn, factories, chooser, 2, LabelGuesserExperiment::XorProbabilities,
                                    "/Users/wachs/SUN/", "guess_reinf_70p_2w_Xor.txt");
    //l2.start();

    LabelGuesserExperimentThread l3(cn, factories, chooser, 3, LabelGuesserExperiment::XorProbabilities,
                                    "/Users/wachs/SUN/", "guess_reinf_70p_3w_Xor.txt");
    //l3.start();
    l1.wait();
    l2.wait();
    l3.wait();
    return 0;
}

int main(int argc, char *argv[]) {
    time_t inicio = time(0);

    printf("tempo = %f\n", (time(0) - inicio) / 60. / 60.);

    ConfigFileParser config(argv[1]);
    FeaturesComplexNetwork cn = config.getComplexNetwork();
    bool constructor_enabled = config.getValue("constructor_general/constructor_enabled").toBool();
    bool constructor_save = config.getValue("constructor_general/save").toBool();
    bool guesser_execute = config.getValue("label_guesser_experiment/execute").toBool();
    QString guesser_output = config.getValue("label_guesser_experiment/output_file").toString();
    int walk_length = config.getValue("label_guesser_experiment/walk_length").toInt();
    LabelGuesserExperiment::method method;
    bool useLabels = config.getValue("label_guesser_experiment/use_labels", true).toBool();

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
        ComplexNetworkConstructor constructor = config.getConstructor(cn);
        if (constructor_enabled) {
            constructor.build();
            if (constructor_save)
                cn.save(config.getValue("FeaturesComplexNetwork/file").toString().toStdString().c_str());
        }
    }


    RegionChooser region_chooser = config.getRegionChooser();

    if (guesser_execute) {
        LabelGuesserExperiment l1(cn, config.getFactories(), region_chooser, walk_length, method, useLabels);
        printf("Iniciando experimento\n");
        l1.execute(guesser_output);
        printf("Terminado\n");
        printf("Tempo total %.2f horas\n", (time_t(0) - inicio) / 60.0 / 60.0);
    }

    return 0;
}
