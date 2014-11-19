
#include <stdio.h>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <QVector>
#include <GuiUtilities/SupervisedImageViewerWidget.hpp>
#include <QApplication>
#include "AreaFeatureExtractionWindow.hpp"
#include <QString>

const char *helpText=\
        "usage: AreaFeatureExtractionTest <pathToSunDatabase>\n"\
        "\n"\
        "Arguments:\n"\
        "  pathToSunDatabase:  this folder must contains 'Annotations' and 'Images' subfolders\n";

int main(int argc, char* argv[]){


    printf("\n\n%f \n", (atan2(1, 0)*180./M_PI ));
    printf("%f \n", (atan2(0, 1)*180./M_PI ));
    printf("%f \n", (atan2(-1, 0)*180./M_PI));
    printf("%f \n", (atan2(0, -1)*180./M_PI));
    return 0;

    if(argc==1){
        printf("%s", helpText);
        return 0;
    }
    QApplication app(argc,argv);

    AreaFeatureFactory e(5);
    SunDatabaseReader reader( (QString(argv[1])) );
    SupervisedImage s = reader.readNext();

    FeatureAbstract* v = e.CreateFromRegion(&(s.getRegions()[0]));
    AreaFeatureExtractionWindow win(argv[1]);
    win.setVisible(true);




    return app.exec();

}
