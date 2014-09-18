

#ifndef SUN_DATABASE_READER__HPP
#define SUN_DATABASE_READER__HPP

#include "DatabaseReader.hpp"
#include <QString>
#include <QDir>
#include <assert.h>

class SunDatabaseReader:public DatabaseReader{

    private:
        QDir sourceDir;

    public:
        SunDatabaseReader(QString sourceDir);
        SupervisedImage readNext();

};



#endif
