//
// Created by Guilherme Wachs on 06/08/15.
//

#include "FrequentLabels.hpp"
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <QHash>
#include <QMap>
#include <QFile>
#include <QList>
#include <FeatureExtractors/Region.hpp>
#include <qtextstream.h>
#include <QCoreApplication>
#include <Utilities/Utils.hpp>
#include <Utilities/tictac.h>

FrequentLabels::FrequentLabels(QString sunPath, QString outputFile) {
    SunDatabaseReader reader(sunPath);
    QMap<QString, int> index;
    typedef QPair<QString, int> reg;
    QList<reg> ordered;
    tictac::tic();
    while(reader.hasNext() ){
        SupervisedImage img = reader.readNext();
        QList<Region> regions = img.getRegions();
        for( Region &r : regions ){
            if( index.contains(r.getLabel()) ){
                index[r.getLabel()]++;
            }else{
                index[r.getLabel()] = 1;
            }
        }
    }
    for( QString k : index.keys() ){
        ordered.append(reg(k, index[k]));
    }

    qSort(ordered.begin(), ordered.end(), [](const reg &a, const reg &b){return a.second > b.second;});

    QFile output(outputFile);
    output.open(QIODevice::WriteOnly);
    QTextStream outputStream(&output);
    for( reg &k : ordered ){
        outputStream << k.first << "\t" << k.second << "\n";
    }
    output.close();
    tictac::tac();

}
