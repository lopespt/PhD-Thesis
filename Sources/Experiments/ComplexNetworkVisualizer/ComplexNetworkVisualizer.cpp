#include "ComplexNetworkVisualizer.hpp"
#include <Utilities/ComplexNetworkConstructor.hpp>
#include <Utilities/SunDatabaseReader.hpp>

ComplexNetworkVisualizer::ComplexNetworkVisualizer(QWidget *parent) :
    QMainWindow(parent)
{
    this->viewer = new ComplexNetworkViewerWidget;
    setCentralWidget(viewer);
}


void ComplexNetworkVisualizer::load(const QString &file, QList<FeatureFactoryAbstract*> factories){
    cn.load(file.toStdString().c_str(), factories);
    printf("Total Nodes: %u\n", cn.getNumNodes());
    printf("Total Edges: %u\n", cn.getNumEdges());
    viewer->setComplexNetwork(cn);
}

