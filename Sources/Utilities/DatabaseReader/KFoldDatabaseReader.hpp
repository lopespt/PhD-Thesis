#ifndef KFOLDDATABASEREADER_HPP
#define KFOLDDATABASEREADER_HPP

#include <QList>
#include "DatabaseReader.hpp"
#include <QString>
#include <mutex>

class SupervisedImage;

class KFoldDatabaseReader {
private:
    QList<QString> trainImages;
    QList<QString> testImages;

    static QList<int> randomPermutation(int n);

public:
    KFoldDatabaseReader(DatabaseReader &reader, float trainRatio);

    KFoldDatabaseReader(QString filePath);


    class PathDatabaseReader : public DatabaseReader {
    private:
        mutable std::mutex mtx;
        QList<QString> images;
        unsigned int current;

        SupervisedImage readAt(unsigned int i);

        PathDatabaseReader(QList<QString> images);
        PathDatabaseReader(const PathDatabaseReader& other){
            this->images = other.images;
            this->current = other.current;
            this->mtx.unlock();
        }


    public:
        virtual SupervisedImage readNext();

        virtual SupervisedImage readPrevious();

        virtual bool hasNext() const;

        virtual bool hasPrevious() const;

        virtual unsigned int getTotal() const;

        friend class KFoldDatabaseReader;
    };

    PathDatabaseReader getTrainReader() const;

    PathDatabaseReader getTestReader() const;

    void save(QString filePath) const;

    void load(QString filePath);


};

#endif // KFOLDDATABASEREADER_HPP
