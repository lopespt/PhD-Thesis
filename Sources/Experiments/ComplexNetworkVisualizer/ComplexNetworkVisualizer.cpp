#include "ComplexNetworkVisualizer.hpp"

#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Utilities/FeaturesComplexNetwork.hpp>

#include <QWidget>
#include "ComplexNetworkViewerWidget.hpp"

ComplexNetworkVisualizer::ComplexNetworkVisualizer(QWidget *parent) :
    QMainWindow(parent)
{
    this->viewer = new ComplexNetworkViewerWidget;
    setCentralWidget(viewer);
}


void ComplexNetworkVisualizer::load(const QString &file, QList<FeatureFactoryAbstract*> factories){
    cn.load(file.toStdString().c_str(), factories);
    printf("Total Nodes: %u\n", cn.getNumNodes());
    printf("Total Edges: %u\n", cn.getNumArcs());
    viewer->setComplexNetwork(cn);
}

