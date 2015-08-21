//
// Created by Guilherme Wachs on 20/08/15.
//

#ifndef PHDTHESIS_CONFIGPARSER_H
#define PHDTHESIS_CONFIGPARSER_H

#include <QCommandLineParser>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include <QList>
#include <QString>
#include <QSettings>

class ConfigParser : private QCommandLineParser{
    QSettings *settings;

public:
    ConfigParser(const QCoreApplication &app);

    bool hasToBuildCN();
    QString getCnOutput();
    QString getCnInput();
    QString getDatabasePath();
    QString getGuesserOutput();
    float getKFoldTrainPercentage();
    QString getKFoldFilePath();
    QString getChoosenRegionFilePath();


    int getNumThreads();

    QList<const FeatureFactoryAbstract*> getFactories();
    virtual bool addOption(const QCommandLineOption &commandLineOption);
    QString getPreferedValue(const QString &configKey, const QString &commKey, const QString &def = "");

    virtual ~ConfigParser();

};


#endif //PHDTHESIS_CONFIGPARSER_H
