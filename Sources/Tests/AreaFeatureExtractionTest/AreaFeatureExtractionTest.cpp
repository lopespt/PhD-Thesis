
#include <stdio.h>
#include <FeatureExtractors/AreaFeatureExtractor.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <QVector>
#include <GuiUtilities/supervisedimageviewerwidget.hpp>
#include <QApplication>
#include "AreaFeatureExtractionWindow.hpp"

int main(int argc, char* argv[]){

    QApplication app(argc,argv);

    //AreaFeatureExtractor e;
    //QVector<float> v = e.doExtraction(s.getRegions()[0], 5);
    AreaFeatureExtractionWindow win;
    win.setVisible(true);

    return app.exec();

}
