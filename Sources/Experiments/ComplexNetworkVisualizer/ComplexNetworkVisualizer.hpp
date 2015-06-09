#ifndef COMPLEXNETWORKVISUALIZER_HPP
#define COMPLEXNETWORKVISUALIZER_HPP

#include <QMainWindow>
#include <QList>
#include <Utilities/FeaturesComplexNetwork.hpp>


class ComplexNetworkViewerWidget;

class FeatureFactoryAbstract;

class QWidget;

class QString;


class ComplexNetworkVisualizer : public QMainWindow {
Q_OBJECT
private:
    FeaturesComplexNetwork cn;
    ComplexNetworkViewerWidget *viewer;
public:
    explicit ComplexNetworkVisualizer(QWidget *parent = 0);

    void load(const QString &file, QList<const FeatureFactoryAbstract *> factories);

signals:

public slots:

};

#endif // COMPLEXNETWORKVISUALIZER_HPP
