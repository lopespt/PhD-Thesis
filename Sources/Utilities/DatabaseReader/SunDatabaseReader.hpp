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
#include <mutex>

class SunDatabaseReader : public DatabaseReader {

private:
    mutable std::mutex mtx;
    QDir sourceDir;
    QList<QString> image_files;
    QList<QString> supervision_files;

    void discover_files(QString);

    QList<QString>::iterator image_files_it;
    QList<QString>::iterator supervision_files_it;
    bool started;


public:
    SunDatabaseReader(QString sourceDir);
    SunDatabaseReader(const SunDatabaseReader& other);

    bool hasNext() const;

    SupervisedImage readNext();

    bool hasPrevious() const;

    SupervisedImage readPrevious();

    unsigned int getTotal() const;

};


#endif
