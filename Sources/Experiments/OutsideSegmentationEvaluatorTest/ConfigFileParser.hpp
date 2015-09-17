#ifndef CONFIGFILEPARSER_HPP
#define CONFIGFILEPARSER_HPP

#include <QString>
#include <QSettings>
#include <QList>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructorP.hpp>

class FeatureFactoryAbstract;

class ComplexNetworkConstructor;

class DatabaseReader;

class CoOcurrenceEquation;

class FeaturesComplexNetwork;

class RegionChooser;

class KFoldDatabaseReader;

class ConfigFileParser {
private:
    QSettings settings;
    QList<const FeatureFactoryAbstract *> factoriesCreated;

    DatabaseReader *trainDatabaseCreated;
    DatabaseReader *testDatabaseCreated;
    CoOcurrenceEquation *coocurrenceCreated;
    KFoldDatabaseReader *kfoldCreated;

    void loadKfold();

public:
    ConfigFileParser(QString filePath);

    QList<const FeatureFactoryAbstract *> getFactories();

    ComplexNetworkConstructorP getConstructorP(FeaturesComplexNetwork &cn, int threads=1);
    ComplexNetworkConstructor getConstructor(FeaturesComplexNetwork &cn);

    DatabaseReader *getTrainDatabaseReader();

    DatabaseReader *getTestDatabaseReader();

    void getComplexNetwork(FeaturesComplexNetwork &cn);

    RegionChooser getRegionChooser();

    QVariant getValue(QString str, QVariant def = QVariant());

    bool cnLoaded();

    ~ConfigFileParser();
};

#endif // CONFIGFILEPARSER_HPP
