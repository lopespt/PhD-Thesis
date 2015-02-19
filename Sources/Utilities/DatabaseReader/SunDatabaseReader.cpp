
#include "SunDatabaseReader.hpp"
#include "../SupervisedImage.hpp"

SunDatabaseReader::SunDatabaseReader(QString sourceDir):sourceDir(sourceDir){
    assert(this->sourceDir.exists());
    assert(this->sourceDir.exists("Annotations"));
    assert(this->sourceDir.exists("Images"));

    discover_files(this->sourceDir.absolutePath()+"/Images");
    image_files_it = image_files.begin();
    supervision_files_it = supervision_files.begin();
    started = false;
}

bool SunDatabaseReader::hasNext() const{
    return image_files_it+1 != image_files.end();
}

SupervisedImage  SunDatabaseReader::readNext() {
    assert( image_files_it != image_files.end() );
    if(started){
        image_files_it++;
        supervision_files_it++;
    }
    started=true;
    SupervisedImage ret(*image_files_it, *supervision_files_it  );
    return ret;
}

bool SunDatabaseReader::hasPrevious() const{
    return image_files_it != image_files.begin();
}

SupervisedImage  SunDatabaseReader::readPrevious() {
    assert( image_files_it != image_files.begin() );
    SupervisedImage ret(*(image_files_it-1), *(supervision_files_it-1)  );
    if(image_files_it != image_files.begin()){
     image_files_it--;
     supervision_files_it--;
    }
    return ret;
}

void SunDatabaseReader::discover_files(QString path){
    QDir d(path);
    QFileInfoList files_list = d.entryInfoList(QDir::Files);
    for(QFileInfo f: files_list){
        this->image_files.append(f.absoluteFilePath());

        QString fsupervised = f.absoluteFilePath();
        fsupervised = fsupervised.replace( this->sourceDir.absolutePath()+"/Images", this->sourceDir.absolutePath()+"/Annotations");
        fsupervised = fsupervised.replace(".jpg", ".xml");
        this->supervision_files.append(fsupervised);

        //printf("%s\n", f.absoluteFilePath().toStdString().c_str());
        //printf("%s\n", fsupervised.toStdString().c_str());
    }

    QFileInfoList folders_list = d.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);
    for(QFileInfo f: folders_list){
        this->discover_files(f.absoluteFilePath());
    }
}

unsigned int SunDatabaseReader::getTotal() const{
    return this->image_files.size();
}
