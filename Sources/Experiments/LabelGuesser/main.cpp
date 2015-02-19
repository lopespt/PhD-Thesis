
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

void createFiles(){
    FeaturesComplexNetwork cn;
    SunDatabaseReader reader("/Users/wachs/SUN");

    KFoldDatabaseReader kfold(reader, 0.7);
    kfold.save("images_set.kfold");

    KFoldDatabaseReader::PathDatabaseReader testSet = kfold.getTestReader();
    KFoldDatabaseReader::PathDatabaseReader trainSet = kfold.getTrainReader();


    QList<FeatureFactoryAbstract*> factories;
    LabelFeatureFactory l;
    factories.append(&l);
    ComplexNetworkConstructor constructor(cn, trainSet, factories);
    constructor.build();
    cn.refreshCache();
    cn.save("train_labels.cn");
    RegionChooser chooser(testSet);
    chooser.save("chosenRegions.txt");
}

int main(int argc, char *argv[]){

    QCoreApplication app(argc, argv);
    //createFiles();
    //return 0;

    FeaturesComplexNetwork cn;

    QList<FeatureFactoryAbstract*> factories;
    LabelFeatureFactory l;
    factories.append(&l);
    cn.load("train_labels.cn", factories);

    RegionChooser chooser("chosenRegions.txt");
    printf("Iniciando experimentos\n");

    LabelGuesserExperimentThread l1(cn, chooser ,1, LabelGuesserExperiment::XorProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_1w_Xor.txt");
    l1.start();

    LabelGuesserExperimentThread l2(cn, chooser ,2, LabelGuesserExperiment::XorProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_2w_Xor.txt");
    l2.start();

    LabelGuesserExperimentThread l3(cn, chooser ,3, LabelGuesserExperiment::XorProbabilities,"/Users/wachs/SUN/", "guess_reinf_70p_3w_Xor.txt");
    l3.start();
    l1.wait();
    l2.wait();
    l3.wait();
    return 0;
}
