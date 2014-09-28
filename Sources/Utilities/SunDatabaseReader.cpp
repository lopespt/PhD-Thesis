
#include <SunDatabaseReader.hpp>

SunDatabaseReader::SunDatabaseReader(QString sourceDir):sourceDir(sourceDir){
    assert(this->sourceDir.exists());
    assert(this->sourceDir.exists("Annotations"));
    assert(this->sourceDir.exists("Images"));

    discover_files(this->sourceDir.absolutePath()+"/Images");
    image_files_it = image_files.begin();
    supervision_files_it = supervision_files.begin();
}

SupervisedImage*  SunDatabaseReader::readNext(){
    if( image_files_it == image_files.end() )
        return NULL;

    SupervisedImage* ret =  new  SupervisedImage(*image_files_it, *supervision_files_it  );
    image_files_it++;
    supervision_files_it++;
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
