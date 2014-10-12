
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

    AreaFeatureExtractor e;
    SunDatabaseReader reader( (QString(argv[1])) );
    SupervisedImage s = reader.readNext();

    HsvHistFeatureExtractor hsv;
    hsv.doExtraction(s.getRegions()[0], 100);

    QVector<float> v = e.doExtraction(s.getRegions()[0], 5);
    AreaFeatureExtractionWindow win(argv[1], 0);
    win.setVisible(true);




    return app.exec();

}
