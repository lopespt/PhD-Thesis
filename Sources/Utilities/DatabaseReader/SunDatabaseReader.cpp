#include "SunDatabaseReader.hpp"
#include "../SupervisedImage.hpp"

SunDatabaseReader::SunDatabaseReader(const SunDatabaseReader &other) {
    this->image_files = other.image_files;
    this->image_files_it = this->image_files.begin();
    this->mtx.unlock();
    this->sourceDir = other.sourceDir;
    this->started = false;
    this->supervision_files = other.supervision_files;
    this->supervision_files_it = this->supervision_files.begin();

}

SunDatabaseReader::SunDatabaseReader(QString sourceDir) : sourceDir(sourceDir) {
    assert(this->sourceDir.exists());
    assert(this->sourceDir.exists("Annotations"));
    assert(this->sourceDir.exists("Images"));

    discover_files(this->sourceDir.absolutePath() + "/Images");
    image_files_it = image_files.begin();
    supervision_files_it = supervision_files.begin();
    started = false;
}

bool SunDatabaseReader::hasNext() const {
    mtx.lock();
    auto ret = image_files_it + 1 != image_files.end();
    mtx.unlock();
    return  ret;
}

SupervisedImage  SunDatabaseReader::readNext() {
    mtx.lock();
    assert(image_files_it != image_files.end());
    if (started) {
        image_files_it++;
        supervision_files_it++;
    }
    started = true;
    SupervisedImage ret(*image_files_it, *supervision_files_it);
    mtx.unlock();
    return ret;
}

bool SunDatabaseReader::hasPrevious() const {
    mtx.lock();
    auto ret = image_files_it != image_files.begin();
    mtx.unlock();
    return ret;
}

SupervisedImage  SunDatabaseReader::readPrevious() {
    mtx.lock();
    assert(image_files_it != image_files.begin());
    SupervisedImage ret(*(image_files_it - 1), *(supervision_files_it - 1));
    if (image_files_it != image_files.begin()) {
        image_files_it--;
        supervision_files_it--;
    }
    mtx.unlock();
    return ret;
}

void SunDatabaseReader::discover_files(QString path) {
    QDir d(path);
    QFileInfoList files_list = d.entryInfoList(QDir::Files);
    for (QFileInfo f: files_list) {
        this->image_files.append(f.absoluteFilePath());

        QString fsupervised = f.absoluteFilePath();
        fsupervised = fsupervised.replace(this->sourceDir.absolutePath() + "/Images",
                                          this->sourceDir.absolutePath() + "/Annotations");
        fsupervised = fsupervised.replace(".jpg", ".xml");
        this->supervision_files.append(fsupervised);

        //printf("%s\n", f.absoluteFilePath().toStdString().c_str());
        //printf("%s\n", fsupervised.toStdString().c_str());
    }

    QFileInfoList folders_list = d.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for (QFileInfo f: folders_list) {
        this->discover_files(f.absoluteFilePath());
    }
}

unsigned int SunDatabaseReader::getTotal() const {
    return (unsigned int) this->image_files.size();
}

