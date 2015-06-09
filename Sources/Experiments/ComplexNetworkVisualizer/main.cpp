#include <QApplication>
#include "ComplexNetworkVisualizer.hpp"
#include <QCommandLineParser>
#include <QVTKApplication.h>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>

int main(int argc, char *argv[]) {

    QVTKApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addPositionalArgument("input", "Input Complex Network File", "input");
    parser.addPositionalArgument("node_type", "One of the following: NodeString, int, float, double", "node_type");

    parser.addHelpOption();
    parser.process(app);

    QList<const FeatureFactoryAbstract *> factories;
    LabelFeatureFactory labelFactory;
    OrientationFeatureFactory orientationFactory(40);
    AreaFeatureFactory areaFactory(10);
    factories.append(&labelFactory);
    factories.append(&orientationFactory);
    factories.append(&areaFactory);


    //FeaturesComplexNetwork cn;
    //cn.load(parser.positionalArguments().first().toStdString().c_str(), factories);
    //printf("%d\n", cn.getNumNodes());
    //printf("%d\n", cn.getNumArcs());
    //fflush(stdout);

    ComplexNetworkVisualizer visualizer;
    visualizer.load(parser.positionalArguments().first(), factories);
    visualizer.setVisible(true);

    return app.exec();
}

