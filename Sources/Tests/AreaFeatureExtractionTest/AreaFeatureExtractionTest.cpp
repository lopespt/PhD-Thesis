
#include <stdio.h>
#include <FeatureExtractors/AreaFeatureExtractor.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <QVector>
#include <GuiUtilities/supervisedimageviewerwidget.hpp>
#include <QApplication>
#include "AreaFeatureExtractionWindow.hpp"


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

    //AreaFeatureExtractor e;
    //QVector<float> v = e.doExtraction(s.getRegions()[0], 5);
    AreaFeatureExtractionWindow win(argv[1]);
    win.setVisible(true);

    return app.exec();

}
