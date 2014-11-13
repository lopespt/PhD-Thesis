#include "SUNRandomFolderGenerator.hpp"

#include <QFile>
#include <assert.h>
#include <Utilities/SunDatabaseReader.hpp>
#include <QList>
#include <QString>
#include <Utilities/SupervisedImage.hpp>
#include <QPair>
#include <QDir>

SUNRandomFolderGenerator::SUNRandomFolderGenerator(QString inputFolder, QString outputFolder, unsigned int num):inputFolder(inputFolder), outputFolder(outputFolder), num(num)
{
}

void SUNRandomFolderGenerator::run(){
    SunDatabaseReader reader(inputFolder);

    unsigned int total = reader.getTotal();
    QList<unsigned int> index = shuffledList(num, total);

    unsigned int s=0;
    while(reader.hasNext()){
        SupervisedImage im = reader.readNext();
        if( index.contains(s) ){
            copy(im.getImagePath());
            copy(im.getSupervisedPath());
        }
        s++;
    }


}

void SUNRandomFolderGenerator::copy(QString path){
    QString relativePath = path.right( path.size() - inputFolder.size() + 1);
    QString newPath = outputFolder+relativePath;
    printf("copying %s to %s\n", relativePath.toStdString().c_str(), newPath.toStdString().c_str());
    QDir dir;
    dir.mkpath(newPath.left(newPath.lastIndexOf("/")));
    QFile::copy(path, outputFolder + relativePath);

}

QList<unsigned int> SUNRandomFolderGenerator::shuffledList(int n, int max){

    QList<unsigned int> index;
    QList<unsigned int> ret;
    for(unsigned int i=0;i<max;i++)
        index.append(i);

    srand(time(NULL));
    for(unsigned int i=0;i<max;i++){
        unsigned int p = rand()%max;
        unsigned int temp = index[i];
        index[i] = index[p];
        index[p] = temp;
    }


    for(unsigned int i=0;i<n && i<max;i++)
        ret.append(index[i]);

    return ret;

}
