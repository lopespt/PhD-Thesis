//
// Created by Guilherme Wachs on 06/08/15.
//

#include "FrequentLabels.hpp"
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <QHash>
#include <QList>
#include <FeatureExtractors/Region.hpp>

FrequentLabels::FrequentLabels(QString sunPath, QString outputFile) {
    SunDatabaseReader reader(sunPath);
    QHash<QString, int> index;
    QList<long> frequency;

    while(reader.hasNext()){
        SupervisedImage img = reader.readNext();
        QList<Region> regions = img.getRegions();
        for( Region &r : regions ){
            if( index.contains(r.getLabel()) ){
                frequency[index[r.getLabel()]]++;
            }else{
                index[r.getLabel()] = frequency.size();
                frequency.append(1);
            }
        }
    }

}
