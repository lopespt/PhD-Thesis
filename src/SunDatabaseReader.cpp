
#include "SunDatabaseReader.hpp"

SunDatabaseReader::SunDatabaseReader(QString sourceDir):sourceDir(sourceDir){
    assert(this->sourceDir.exists());
    assert(this->sourceDir.exists());
    assert(this->sourceDir.exists());

}

SupervisedImage SunDatabaseReader::readNext(){
    return SupervisedImage();
}

