
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL);
VTK_MODULE_INIT(vtkInteractionStyle);

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <QApplication>
#include <gMainWindow.hpp>
#include <QVTKApplication.h>
#include <Utilities/Link.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include "LabelsComplexNetworkConstructor.hpp"
#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLinkButton>
#include <QStringList>
#include <Utilities/ComplexNetworkConstructor.hpp>
#include <Utilities/FeaturesComplexNetwork.hpp>
#include <FeatureExtractors/LabelFeature.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <QList>

int main(int argc, char **argv){

    QCoreApplication app(argc,argv);
    QCommandLineParser parser;
    parser.addPositionalArgument("folder", "SUN Database Folder","folder");
    parser.addOption(QCommandLineOption("o", "Output File","file","complex_network.cn"));
    parser.addHelpOption();

    QString folder;
    parser.process(app);

    folder = parser.positionalArguments().first();

    printf("%s", folder.toStdString().c_str());
    FeaturesComplexNetwork labels_cn;
    SunDatabaseReader reader(folder);
    QList<FeatureFactoryAbstract*> factories;
    LabelFeatureFactory labels_factory;
    factories.append(&labels_factory);

    //LabelsComplexNetworkConstructor constructor(labels_cn, reader);
    //constructor.build();
    ComplexNetworkConstructor constructor(labels_cn,reader,factories);
    constructor.build();
    printf("%u\n", labels_cn.getNumNodes());
    printf("%u", labels_cn.getNumEdges());

    labels_cn.save(parser.value("o").toStdString().c_str());
    return 0;



}


