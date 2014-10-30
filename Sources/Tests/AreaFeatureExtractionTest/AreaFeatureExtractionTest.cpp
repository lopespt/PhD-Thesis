
#include <stdio.h>
#include <FeatureExtractors/AreaFeatureExtractor.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <QVector>
#include <GuiUtilities/SupervisedImageViewerWidget.hpp>
#include <QApplication>
#include "AreaFeatureExtractionWindow.hpp"
#include <FeatureExtractors/HsvHistFeatureExtractor.hpp>
#include <QString>

const char *helpText=\
        "usage: AreaFeatureExtractionTest <pathToSunDatabase>\n"\
        "\n"\
        "Arguments:\n"\
        "  pathToSunDatabase:  this folder must contains 'Annotations' and 'Images' subfolders\n";

int main(int argc, char* argv[]){

    if(argc==1){
        printf("%s", helpText);
        return 0;
    }
    QApplication app(argc,argv);

    int discretization=5;
    AreaFeatureExtractor e(&discretization);
    SunDatabaseReader reader( (QString(argv[1])) );
    SupervisedImage s = reader.readNext();

    HsvHistFeatureExtractor hsv(&discretization);
    hsv.doExtraction(&(s.getRegions()[0]), &discretization);

    QVector<float> v = e.doExtraction(&(s.getRegions()[0]), &discretization);
    AreaFeatureExtractionWindow win(argv[1]);
    win.setVisible(true);




    return app.exec();

}
