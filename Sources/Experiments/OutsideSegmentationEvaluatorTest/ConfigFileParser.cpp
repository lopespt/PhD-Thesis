#include "ConfigFileParser.hpp"

#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Utilities/DatabaseReader/RegionChooser.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <Utilities/ComplexNetworkConstructor/ReinforcementCoOcurrenceEquation.hpp>
#include <Utilities/ComplexNetworkConstructor/AddOneCoOcurrenceEquation.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructorP.hpp>

ConfigFileParser::ConfigFileParser(QString filePath) : settings(filePath, QSettings::IniFormat),
                                                       trainDatabaseCreated(NULL),
                                                       testDatabaseCreated(NULL),
                                                       coocurrenceCreated(NULL),
                                                       kfoldCreated(NULL) {

}

QList<const FeatureFactoryAbstract *> ConfigFileParser::getFactories() {
    if (!factoriesCreated.empty())
        return factoriesCreated;

    if (settings.value("factories_enabled/labels").toBool())
        factoriesCreated.append(new LabelFeatureFactory());
    if (settings.value("factories_enabled/hsv").toBool()) {
        int hd = settings.value("factories/hsv/hue_discretization").toInt();
        int sd = settings.value("factories/hsv/saturation_discretization").toInt();
        int vd = settings.value("factories/hsv/value_discretization").toInt();
        int fd = settings.value("factories/hsv/frequency_discretization").toInt();
        factoriesCreated.append(new HsvFeatureFactory(hd, sd, vd, fd));
    }
    if (settings.value("factories_enabled/orientation").toBool()) {
        int d = settings.value("factories/orientation/orientation_discretization").toInt();
        factoriesCreated.append(new OrientationFeatureFactory(d));
    }
    if (settings.value("factories_enabled/area").toBool()) {
        int d = settings.value("factories/area/area_discretization").toInt();
        factoriesCreated.append(new AreaFeatureFactory(d));
    }

    return factoriesCreated;
}


void ConfigFileParser::loadKfold() {
    if (kfoldCreated)
        return;

    QString database = settings.value("global/databaseReader").toString();
    if (database.toLower() == "kfold") {
        QString path = settings.value("kfold/file").toString();
        if (settings.value("kfold/load").toBool()) {
            kfoldCreated = new KFoldDatabaseReader(path);
            trainDatabaseCreated = new KFoldDatabaseReader::PathDatabaseReader(kfoldCreated->getTrainReader());
            testDatabaseCreated = new KFoldDatabaseReader::PathDatabaseReader(kfoldCreated->getTestReader());
        } else {
            QString sunPath = settings.value("sun/database_path").toString();
            float trainPerc = settings.value("kfold/train_percentage").toFloat();
            SunDatabaseReader sunReader = SunDatabaseReader(sunPath);
            kfoldCreated = new KFoldDatabaseReader(sunReader, trainPerc);
            if (settings.value("kfold/save").toBool())
                kfoldCreated->save(path);

        }
    }
}

DatabaseReader *ConfigFileParser::getTrainDatabaseReader() {
    if (trainDatabaseCreated)
        return trainDatabaseCreated;

    QString database = settings.value("global/databaseReader").toString();
    if (database.toLower() == "kfold") {
        loadKfold();
        trainDatabaseCreated = new KFoldDatabaseReader::PathDatabaseReader(kfoldCreated->getTrainReader());
    } else if (database.toLower() == "sun") {
        QString sunPath = settings.value("sun/database_path").toString();
        trainDatabaseCreated = new SunDatabaseReader(sunPath);
    }

    return trainDatabaseCreated;
}

DatabaseReader *ConfigFileParser::getTestDatabaseReader() {
    if (testDatabaseCreated)
        return testDatabaseCreated;

    QString database = settings.value("global/databaseReader").toString();
    if (database.toLower() == "kfold") {
        testDatabaseCreated = new KFoldDatabaseReader::PathDatabaseReader(kfoldCreated->getTestReader());
    } else if (database.toLower() == "sun") {
        QString sunPath = settings.value("sun/database_path").toString();
        testDatabaseCreated = new SunDatabaseReader(sunPath);
    }

    return testDatabaseCreated;
}

ComplexNetworkConstructorP ConfigFileParser::getConstructorP(FeaturesComplexNetwork &cn, int threads){
    if (coocurrenceCreated)
    return ComplexNetworkConstructorP(cn, *getTrainDatabaseReader(), getFactories(), threads,
                                      coocurrenceCreated);

    QString coocurrenceEqn = settings.value("constructor_general/coocurrence_equation").toString().toLower();
    if (coocurrenceEqn == "add") {
        coocurrenceCreated = new AddOneCoOcurrenceEquation();
    } else if (coocurrenceEqn == "reinforcement") {
        float learningRate = settings.value("constructor/reinforcement/learningRate").toFloat();
        float lambda = settings.value("constructor/reinforcement/lambda").toFloat();
        coocurrenceCreated = new ReinforcementCoOcurrenceEquation(learningRate, lambda);
    }

    return ComplexNetworkConstructorP(cn, *getTrainDatabaseReader(), getFactories(), threads, coocurrenceCreated);
}
ComplexNetworkConstructor ConfigFileParser::getConstructor(FeaturesComplexNetwork &cn) {
    if (coocurrenceCreated)
        return ComplexNetworkConstructor(cn, *getTrainDatabaseReader(), getFactories(), coocurrenceCreated);

    QString coocurrenceEqn = settings.value("constructor_general/coocurrence_equation").toString().toLower();
    if (coocurrenceEqn == "add") {
        coocurrenceCreated = new AddOneCoOcurrenceEquation();
    } else if (coocurrenceEqn == "reinforcement") {
        float learningRate = settings.value("constructor/reinforcement/learningRate").toFloat();
        float lambda = settings.value("constructor/reinforcement/lambda").toFloat();
        coocurrenceCreated = new ReinforcementCoOcurrenceEquation(learningRate, lambda);
    }

        return ComplexNetworkConstructor(cn, *getTrainDatabaseReader(), getFactories(), coocurrenceCreated);

}

bool ConfigFileParser::cnLoaded() {
    return settings.value("FeaturesComplexNetwork/load").toBool();
}

void ConfigFileParser::getComplexNetwork(FeaturesComplexNetwork &cn) {
    if (cnLoaded()) {
        QString path = settings.value("FeaturesComplexNetwork/file").toString();
        cn.load(path.toStdString().c_str(), getFactories());
    }
}

RegionChooser ConfigFileParser::getRegionChooser() {
    QString f = settings.value("region_chooser/file").toString();
    if (settings.value("region_chooser/load").toBool())
        return RegionChooser(f);

    DatabaseReader *reader = getTestDatabaseReader();
    RegionChooser r(*reader);
    if (settings.value("region_chooser/save").toBool())
        r.save(f);

    return r;
}

QVariant ConfigFileParser::getValue(QString str, QVariant def) {
    return settings.value(str, def);
}

ConfigFileParser::~ConfigFileParser() {
    for (const FeatureFactoryAbstract *&f: factoriesCreated) {
        delete f;
    }
    factoriesCreated.clear();

    if (trainDatabaseCreated)
        delete trainDatabaseCreated;

    if (testDatabaseCreated)
        delete testDatabaseCreated;

    if (coocurrenceCreated)
        delete coocurrenceCreated;

    if (kfoldCreated)
        delete kfoldCreated;
}

