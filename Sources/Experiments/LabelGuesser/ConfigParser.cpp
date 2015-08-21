//
// Created by Guilherme Wachs on 20/08/15.
//

#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <QVariant>
#include <QCommandLineOption>
#include "ConfigParser.h"

ConfigParser::ConfigParser(const QCoreApplication &app) {
    addHelpOption();
    addOption(QCommandLineOption(QStringList() << "threads" << "j", "Number of threads for construction", "threads",
                                 "1"));
    addOption(QCommandLineOption(QStringList() << "config" << "c", "Configuration file", "config", ""));
    addOption(QCommandLineOption(QStringList() << "l", "Label feature", "", ""));
    addOption(QCommandLineOption(QStringList() << "H", "HSV H discretization", "h", ""));
    addOption(QCommandLineOption(QStringList() << "s", "HSV S discretization", "s", ""));
    addOption(QCommandLineOption(QStringList() << "v", "HSV V discretization", "v", ""));
    addOption(QCommandLineOption(QStringList() << "y", "HSV Y discretization", "y", ""));
    addOption(QCommandLineOption(QStringList() << "a", "Area discretization", "a", ""));
    addOption(QCommandLineOption(QStringList() << "o", "Orientation discretization", "o", ""));
    addOption(QCommandLineOption(QStringList() << "cno", "Constructor Complex Network output", "cno", ""));
    addOption(QCommandLineOption(QStringList() << "cni", "Complex Network input", "cni", ""));
    addOption(QCommandLineOption(QStringList() << "database", "Image database folder path", "database", ""));
    addOption(QCommandLineOption(QStringList() << "guesses", "Guesser experiment output file", "guesses", ""));
    addOption(QCommandLineOption(QStringList() << "kfold", "kfold filepath", "kfold", ""));
    addOption(QCommandLineOption(QStringList() << "kfoldperc", "kfold percentage", "kfoldperc", ""));
    addOption(QCommandLineOption(QStringList() << "choosen", "Region choosen filepath", "choosen", ""));
    process(app);


    if (!value("config").isEmpty()) {
        settings = new QSettings(value("config"), QSettings::IniFormat);
    } else {
        settings = NULL;
    }


}

QList<const FeatureFactoryAbstract *> ConfigParser::getFactories() {
    if(factoriesCreated.size()>0)
        return factoriesCreated;


    QString h = getPreferedValue("factories/hsv/hue_discretization", "h");
    QString v = getPreferedValue("factories/hsv/value_discretization", "v");
    QString s = getPreferedValue("factories/hsv/saturation_discretization", "s");
    QString y = getPreferedValue("factories/hsv/frequency_discretization", "y");
    QString o = getPreferedValue("factories/orientation/orientation_discretization", "o");
    QString a = getPreferedValue("factories/area/area_discretization", "a");



    bool hLabels = (settings != NULL && settings->value("factories_enabled/labels").toBool()) || isSet("l");
    bool hHSV = (settings != NULL && settings->value("factories_enabled/hsv").toBool()) ||
                (!value("h").isEmpty() && !value("s").isEmpty() && !value("v").isEmpty() && !value("y").isEmpty());
    bool hOri =
            (settings != NULL && settings->value("factories_enabled/orientation").toBool()) || !value("o").isEmpty();
    bool hArea = (settings != NULL && settings->value("factories_enabled/area").toBool()) || !value("a").isEmpty();


    if (hLabels)
        factoriesCreated.append(new LabelFeatureFactory());
    if (hHSV) {
        int hd = h.toInt();
        int sd = s.toInt();
        int vd = v.toInt();
        int fd = y.toInt();
        factoriesCreated.append(new HsvFeatureFactory(hd, sd, vd, fd));
    }
    if (hOri) {
        int d = o.toInt();
        factoriesCreated.append(new OrientationFeatureFactory(d));
    }
    if (hArea) {
        int d = a.toInt();
        factoriesCreated.append(new AreaFeatureFactory(d));
    }

    return factoriesCreated;

}


ConfigParser::~ConfigParser() {
    for(auto &f : factoriesCreated)
        delete f;

    if (settings)
        delete settings;
}

QString ConfigParser::getPreferedValue(const QString &configKey, const QString &commKey, const QString &def) {

    QString setConfig("");
    QString commConfig("");
    if (!commKey.isEmpty()) {
        commConfig = value(commKey);
    }

    if (!configKey.isEmpty()) {
        if (settings) {
            setConfig = settings->value(configKey).toString();
        }
    }

    if (!commConfig.isEmpty())
        return commConfig;
    else if (!setConfig.isEmpty())
        return setConfig;
    else {
        //printf("Nao foi encontrada uma configuracao (%s,%s)\n", configKey.toStdString().c_str(), commKey.toStdString().c_str());
        return QString(def);
    }
}

bool ConfigParser::hasToBuildCN() {
    bool constructor = !value("cno").isEmpty();

    if (!constructor && settings)
        constructor = settings->value("constructor_general/constructor_enabled", "0").toBool();

    return constructor;
}

QString ConfigParser::getCnOutput() {
    QString output;

    output = value("cno");

    if (output.isEmpty() && settings && settings->value("constructor_general/constructor_enabled").toBool() &&
        settings->value("constructor_general/save").toBool()) {
        output = settings->value("FeaturesComplexNetwork/file").toString();
    }

    return output;
}


QString ConfigParser::getCnInput() {
    QString input;

    input = value("cni");

    if (input.isEmpty() && settings && settings->value("FeaturesComplexNetwork/load").toBool()) {
        input = settings->value("FeaturesComplexNetwork/file").toString();
    }

    return input;
}

QString ConfigParser::getDatabasePath() {
    return getPreferedValue("sun/database_path", "database");
}

bool ConfigParser::addOption(const QCommandLineOption &commandLineOption) {
    return QCommandLineParser::addOption(commandLineOption);
}

int ConfigParser::getNumThreads() {
    return getPreferedValue("","threads","1").toInt();
}

QString ConfigParser::getGuesserOutput() {
    QString ret = value("guesses");

    if(ret.isEmpty() && settings && settings->value("label_guesser_experiment/execute").toBool()){
        ret = settings->value("label_guesser_experiment/output_file").toString();
    }
    //assert(!ret.isEmpty());

    return ret;
}

float ConfigParser::getKFoldTrainPercentage() {
    QString ret = value("kfoldperc");

    if(ret.isEmpty() && settings)
        ret = settings->value("kfold/train_percentage").toString();

    assert(!ret.isEmpty());

    return ret.toFloat();
}

QString ConfigParser::getKFoldFilePath() {
    QString ret = value("kfold");

    if(ret.isEmpty() && settings)
        ret = settings->value("kfold/file").toString();

    assert(!ret.isEmpty());

    return ret;
}

QString ConfigParser::getChoosenRegionFilePath() {
    QString ret = value("choosen");

    if(ret.isEmpty() && settings)
        ret = settings->value("region_chooser/file").toString();

    assert(!ret.isEmpty());

    return ret;
}
