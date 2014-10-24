#include "ComplexNetworkVisualizer.hpp"
#include <Utilities/ComplexNetworkConstructor.hpp>
#include <Utilities/SunDatabaseReader.hpp>
#include "../LabelsComplexNetworks/LabelsComplexNetworkConstructor.cpp"
ComplexNetworkVisualizer::ComplexNetworkVisualizer(QWidget *parent) :
    QMainWindow(parent)
{
    this->viewer = new ComplexNetworkViewerWidget;
    setCentralWidget(viewer);
}


void ComplexNetworkVisualizer::load(const QString &file){
    cn.load(file.toStdString().c_str());
    printf("Total Nodes: %lu\n", cn.getNodesCount());
    printf("Total Edges: %lu\n", cn.getEdgesCount());
    viewer->setComplexNetwork(cn);
}

