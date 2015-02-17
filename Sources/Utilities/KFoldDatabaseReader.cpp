#include "KFoldDatabaseReader.hpp"
#include "DatabaseReader.hpp"
#include <math.h>
#include <time.h>
#include "SupervisedImage.hpp"
#include <QSet>
#include <QList>
#include <QString>
#include <assert.h>

KFoldDatabaseReader::KFoldDatabaseReader(DatabaseReader &reader, float trainRatio)
{
    QList<int> randomList = randomPermutation(reader.getTotal());
    int trainSize = trainRatio * reader.getTotal();
    QSet<int> trainSet;
    for(int i=0;i<trainSize;i++){
        trainSet.insert(randomList[i]);
    }

    int i=0;
    while(reader.hasNext()){
        SupervisedImage img = reader.readNext();
        if( trainSet.contains(i) )
            trainImages.append(img.getImagePath());
        else
            testImages.append(img.getImagePath());

        i++;
    }

}

QList<int> KFoldDatabaseReader::randomPermutation(int n){
    QList<int> ret;
    for(int i=0;i<n;i++){
        ret.append(i);
    }
    srand(time(NULL));
    int r;
    int temp;
    for(int i=0;i<n;i++){
        r=rand() % n;
        temp = ret[i];
        ret[i] = ret[r];
        ret[r] = temp;
    }

    return ret;
}

KFoldDatabaseReader::PathDatabaseReader KFoldDatabaseReader::getTestReader() const{
    return KFoldDatabaseReader::PathDatabaseReader(testImages);
}

KFoldDatabaseReader::PathDatabaseReader KFoldDatabaseReader::getTrainReader() const{
    return KFoldDatabaseReader::PathDatabaseReader(trainImages);
}

KFoldDatabaseReader::PathDatabaseReader::PathDatabaseReader(QList<QString> images):images(images), current(0){

}

SupervisedImage KFoldDatabaseReader::PathDatabaseReader::readAt(unsigned int i){
    QString supervision = QString(images[i]);
    supervision = supervision.replace("/Images/","/Annotations/").replace(".jpg", ".xml");
    return SupervisedImage(images[i], supervision);
}

SupervisedImage KFoldDatabaseReader::PathDatabaseReader::readNext(){
    assert(hasNext());
    return readAt(++current);
}

bool KFoldDatabaseReader::PathDatabaseReader::hasNext() const{
    return current < getTotal() - 1;
}

SupervisedImage KFoldDatabaseReader::PathDatabaseReader::readPrevious(){
    assert(hasPrevious());
    return readAt(--current);
}

bool KFoldDatabaseReader::PathDatabaseReader::hasPrevious() const{
    return current > 0;
}

unsigned int KFoldDatabaseReader::PathDatabaseReader::getTotal() const{
    return images.size();
}


