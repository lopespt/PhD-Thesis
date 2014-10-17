#ifndef COMPLEXNETWORKVISUALIZER_HPP
#define COMPLEXNETWORKVISUALIZER_HPP

#include <QMainWindow>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <ComplexNetwork/NodeString.hpp>
#include <ComplexNetworkViewerWidget.hpp>
#include <QVBoxLayout>

class ComplexNetworkVisualizer : public QMainWindow
{
    Q_OBJECT
private:
    ComplexNetwork<NodeString, Link> cn;
    ComplexNetworkViewerWidget *viewer;
public:
    explicit ComplexNetworkVisualizer(QWidget *parent = 0);
    void load(const QString &file);
signals:

public slots:

};

#endif // COMPLEXNETWORKVISUALIZER_HPP
