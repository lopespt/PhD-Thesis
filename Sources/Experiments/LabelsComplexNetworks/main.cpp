
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
    ComplexNetwork<NodeString, Link> labels_cn;
    SunDatabaseReader reader(folder);

    LabelsComplexNetworkConstructor constructor(labels_cn, reader);
    constructor.build();
    labels_cn.save(parser.value("o").toStdString().c_str());
    return 0;



  }


