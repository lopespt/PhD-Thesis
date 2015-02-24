
#include "LabelGuesserExperiment.hpp"
#include <locale.h>
#include <QString>
#include <QCoreApplication>
#include "LabelGuesserExperimentThread.hpp"
#include <Utilities/FeaturesComplexNetwork.hpp>
#include <Utilities/DatabaseReader/RegionChooser.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <QList>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Utilities/DatabaseReader/RegionChooser.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <Utilities/Utils.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include "ConfigFileParser.hpp"

void createFiles(){
    FeaturesComplexNetwork cn;
    SunDatabaseReader reader("/Users/wachs/SUN");

    KFoldDatabaseReader kfold(reader, 0.7);
    kfold.save("images_set.kfold");

    KFoldDatabaseReader::PathDatabaseReader testSet = kfold.getTestReader();
    KFoldDatabaseReader::PathDatabaseReader trainSet = kfold.getTrainReader();


    QList<const FeatureFactoryAbstract*> factories;
    LabelFeatureFactory l;
    HsvFeatureFactory hsv(4,3,3,20);
    factories.append(&l);
 //   factories.append(&hsv);

    ComplexNetworkConstructor constructor(cn, trainSet, factories);
    constructor.build();
    cn.refreshCache();
    cn.save("train_labels.cn");
    RegionChooser chooser(testSet);
    chooser.save("chosenRegions.txt");
}

int main2(int argc, char *argv[]){

    QCoreApplication app(argc, argv);

    createFiles();
    return 0;

    FeaturesComplexNetwork cn;

    QList<const FeatureFactoryAbstract*> factories;
    LabelFeatureFactory l;
    HsvFeatureFactory hsv(4,3,3,20);
    factories.append(&l);
    factories.append(&hsv);
    cn.load("/tmp/Implementation-Build/bin/train_labels.cn", factories);

    RegionChooser chooser("/tmp/Implementation-Build/bin/chosenRegions.txt");
    printf("Iniciando experimentos\n");

    LabelGuesserExperimentThread l1(cn,factories, chooser ,3, LabelGuesserExperiment::XorProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_1w_Xor.txt");
    l1.start();

    LabelGuesserExperimentThread l2(cn,factories, chooser ,2, LabelGuesserExperiment::XorProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_2w_Xor.txt");
    //l2.start();

    LabelGuesserExperimentThread l3(cn,factories, chooser ,3, LabelGuesserExperiment::XorProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_3w_Xor.txt");
    //l3.start();
    l1.wait();
    l2.wait();
    l3.wait();
    return 0;
}

int main(int argc, char *argv[]){
    ConfigFileParser config("config.ini");
    FeaturesComplexNetwork cn = config.getComplexNetwork();
    if(!config.cnLoaded()){
        ComplexNetworkConstructor constructor = config.getConstructor(cn);
        constructor.build();
        if(config.getValue("constructor_general/save").toBool())
            cn.save(config.getValue("FeaturesComplexNetwork/file").toString().toStdString().c_str());
    }

    printf("passei\n");
    LabelGuesserExperiment l1(cn, config.getFactories(), config.getRegionChooser(), 1, LabelGuesserExperiment::XorProbabilities);
    printf("passei\n");
    l1.execute("saida.txt");

    return 0;
}
