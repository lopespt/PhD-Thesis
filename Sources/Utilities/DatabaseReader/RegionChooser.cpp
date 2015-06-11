#include "RegionChooser.hpp"

RegionChooser::RegionChooser(DatabaseReader &reader) {
    srand((unsigned int) time(0));
    while (reader.hasNext()) {
        SupervisedImage img = reader.readNext();
        ChosenRegion reg;
        reg.imagePath = img.getImagePath();
        reg.supervisedPath = img.getSupervisedPath();
        if (img.getRegions().size() > 1) {
            reg.regionChoosed = (unsigned int) (rand() % img.getRegions().size());
            regions.append(reg);
        }
    }
    reset();
}

RegionChooser::RegionChooser(QString file) {
    load(file);
}

void RegionChooser::reset() {
    this->actualRegion = 0;
}

int RegionChooser::getTotal() const {
    return regions.size();
}

bool RegionChooser::hasNextChoseRegion() const {
    return this->actualRegion < regions.size();
}

RegionChooser::ChosenRegion RegionChooser::nextChoseRegion() {
    assert(hasNextChoseRegion());
    return regions.at(actualRegion++);
}

SupervisedImage RegionChooser::ChosenRegion::readSupervisedImage() const {
    return SupervisedImage(this->imagePath, this->supervisedPath);
}

void RegionChooser::save(QString file) const {
    FILE *f = fopen(file.toStdString().c_str(), "w");

    for (const ChosenRegion &r: regions) {
        fprintf(f, "%s\n", r.imagePath.toStdString().c_str());
        fprintf(f, "%s\n", r.supervisedPath.toStdString().c_str());
        fprintf(f, "%u\n", r.regionChoosed);
    }

    fclose(f);
}

void RegionChooser::load(QString file) {
    regions.clear();
    FILE *f = fopen(file.toStdString().c_str(), "r");
    char buffer[400];
    ChosenRegion r;
    while (Utils::readLine(buffer, 400, f) != NULL) {
        r.imagePath = QString(buffer);
        assert(Utils::readLine(buffer, 400, f));
        r.supervisedPath = QString(buffer);
        assert(Utils::readLine(buffer, 400, f));
        sscanf(buffer, "%u", &r.regionChoosed);
        regions.append(r);
    }

    fclose(f);
    reset();
}

RegionChooser::~RegionChooser() {

}

