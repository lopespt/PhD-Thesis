
#include <QApplication>
#include "ComplexNetworkVisualizer.hpp"
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QVTKApplication.h>

int main(int argc, char *argv[]){

    QVTKApplication app(argc, argv);

    QCommandLineParser parser;
    parser.addPositionalArgument("input","Input Complex Network File","input");
    parser.addPositionalArgument("node_type","One of the following: NodeString, int, float, double","node_type");

    parser.addHelpOption();
    parser.process(app);

    ComplexNetworkVisualizer visualizer;
    visualizer.load(parser.positionalArguments().first());
    visualizer.setVisible(true);

    return app.exec();
}

