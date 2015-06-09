#include <stdio.h>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <GuiUtilities/SupervisedImageViewerWidget.hpp>
#include <QApplication>
#include "AreaFeatureExtractionWindow.hpp"

#define _USE_MATH_DEFINES

const char *helpText = \
        "usage: AreaFeatureExtractionTest <pathToSunDatabase>\n"\
        "\n"\
        "Arguments:\n"\
        "  pathToSunDatabase:  this folder must contains 'Annotations' and 'Images' subfolders\n";

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf("%s", helpText);
        return 0;
    }
    QApplication app(argc, argv);

    AreaFeatureFactory e(5);
    SunDatabaseReader reader((QString(argv[1])));
    SupervisedImage s = reader.readNext();

    AreaFeatureExtractionWindow win(argv[1]);
    win.setVisible(true);


    return app.exec();

}
