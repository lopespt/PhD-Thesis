#ifndef COMPLEXNETWORKVISUALIZER_HPP
#define COMPLEXNETWORKVISUALIZER_HPP

#include <QMainWindow>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/NodeString.hpp>
#include <ComplexNetworkViewerWidget.hpp>
#include <QVBoxLayout>
#include <FeatureExtractors/FeatureAbstract.hpp>

class ComplexNetworkVisualizer : public QMainWindow
{
    Q_OBJECT
private:
    ComplexNetwork<FeatureAbstract*, Link> cn;
    ComplexNetworkViewerWidget *viewer;
public:
    explicit ComplexNetworkVisualizer(QWidget *parent = 0);
    void load(const QString &file);
signals:

public slots:

};

#endif // COMPLEXNETWORKVISUALIZER_HPP
