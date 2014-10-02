
#include <stdio.h>
#include <FeatureExtractors/AreaFeatureExtractor.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <QVector>
#include <GuiUtilities/supervisedimageviewerwidget.hpp>
#include <QApplication>

int main(int argc, char* argv[]){

    QApplication app(argc,argv);

    SunDatabaseReader r("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/SunDatabasePartial/");
    SupervisedImage *s = r.readNext();
    SupervisedImageViewerWidget viewer;
    //viewer.setSupervisedImage(s);
    viewer.setVisible(true);

    AreaFeatureExtractor e;

    QVector<float> v = e.doExtraction(s->getRegions()[0], 5);

    for(int i=0;i<v.size();i++)
        printf("%f ", v[i]);

    printf("\nFIM\n");

    delete s;

    return app.exec();

}
