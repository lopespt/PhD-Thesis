

#ifndef SUN_DATABASE_READER__HPP
#define SUN_DATABASE_READER__HPP

#include "DatabaseReader.hpp"
#include <QString>
#include <QDir>
#include <assert.h>
#include <QList>
#include <QFileInfoList>
#include <QFileInfo>
#include <assert.h>

class SunDatabaseReader:public DatabaseReader{

    private:
        QDir sourceDir;
        QList<QString> image_files;
        QList<QString> supervision_files;
        void discover_files(QString);
        QList<QString>::iterator image_files_it;
        QList<QString>::iterator supervision_files_it;
        bool direction_forward;
        

    public:
        SunDatabaseReader(QString sourceDir);
        bool hasNext() const;
        SupervisedImage readNext();
        bool hasPrevious() const;
        SupervisedImage readPrevious();

};



#endif
