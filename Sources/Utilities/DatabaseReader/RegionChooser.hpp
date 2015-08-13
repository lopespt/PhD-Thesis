#ifndef REGIONCHOOSER_HPP
#define REGIONCHOOSER_HPP

#include <QList>
#include <QString>
#include "DatabaseReader.hpp"
#include <Utilities/SupervisedImage.hpp>
#include <mutex>

class RegionChooser {
public:
    class ChosenRegion {
    public:
        QString imagePath;
        QString supervisedPath;
        unsigned int regionChoosed;

        SupervisedImage readSupervisedImage() const;
    };

private:
    QList<ChosenRegion> regions;
    int actualRegion;
public:
    RegionChooser(DatabaseReader &reader);

    RegionChooser(QString file);

    void reset();

    int getTotal() const;

    bool hasNextChoseRegion() const;

    ChosenRegion nextChoseRegion();

    void save(QString file) const;

    void load(QString file);


    ~RegionChooser();
};

#endif // REGIONCHOOSER_HPP
