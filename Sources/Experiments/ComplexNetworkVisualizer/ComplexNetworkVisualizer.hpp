#ifndef COMPLEXNETWORKVISUALIZER_HPP
#define COMPLEXNETWORKVISUALIZER_HPP

#include <QMainWindow>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/NodeString.hpp>
#include <ComplexNetworkViewerWidget.hpp>
#include <QVBoxLayout>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include <Utilities/FeaturesComplexNetwork.hpp>

class ComplexNetworkVisualizer : public QMainWindow
{
    Q_OBJECT
private:
    FeaturesComplexNetwork cn;
    ComplexNetworkViewerWidget *viewer;
public:
    explicit ComplexNetworkVisualizer(QWidget *parent = 0);
    void load(const QString &file, QList<FeatureFactoryAbstract*> factories);
signals:

public slots:

};

#endif // COMPLEXNETWORKVISUALIZER_HPP
