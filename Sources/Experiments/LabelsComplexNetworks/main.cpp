#include <vtkAutoInit.h>

VTK_MODULE_INIT(vtkRenderingOpenGL);

VTK_MODULE_INIT(vtkInteractionStyle);

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <QApplication>
//#include <gMainWindow.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <QCommandLineParser>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <FeatureExtractors/LabelFeature.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <lemon/bellman_ford.h>
#include <lemon/
#include <Utilities/GraphUtilities.hpp>

int main(int argc, char **argv) {
    QCoreApplication app(argc, argv);
    QCommandLineParser parser;
    parser.addPositionalArgument("folder", "SUN Database Folder", "folder");
    parser.addOption(QCommandLineOption("o", "Output File", "file", "complex_network.cn"));
    parser.addOption(QCommandLineOption("m", "Matlab File", "matlab", "mat.m"));
    parser.addHelpOption();

    QString folder;
    parser.process(app);

    folder = parser.positionalArguments().first();


    printf("%s", folder.toStdString().c_str());
    FeaturesComplexNetwork labels_cn;
    SunDatabaseReader reader(folder);
    QList<const FeatureFactoryAbstract *> factories;
    LabelFeatureFactory labels_factory;
    //OrientationFeatureFactory orientation_factory(2000);
    factories.append(&labels_factory);
    ///factories.append(&orientation_factory);

    labels_cn.load("labels.cn", factories);
    FeaturesComplexNetwork::ArcMap<double> dists(labels_cn);
    GraphUtilities::getWeights(labels_cn, dists);
    BellmanFord f(labels_cn, dists);
    f.start()



    ComplexNetworkConstructor constructor(labels_cn, reader, factories);
    constructor.build();
    printf("Nodes: %u\n", labels_cn.getNumNodes());
    printf("Edges: %u", labels_cn.getNumArcs());

    labels_cn.save(parser.value("o").toStdString().c_str());

    FILE *f = fopen(parser.value("m").toStdString().c_str(), "w");

    float deg;
    for(FeaturesComplexNetwork::NodeIt it(labels_cn); it != INVALID; ++it){
            deg = labels_cn.getOutputWeightedDegree(it) + labels_cn.getInputWeightedDegree(it);
            fprintf(f,"%f\n", deg);
    }

    fclose(f);

    return 0;


}


