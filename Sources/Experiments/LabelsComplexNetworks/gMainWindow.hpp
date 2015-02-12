#ifndef GMAINWINDOW_HPP
#define GMAINWINDOW_HPP

#include <QWidget>
#include <vtkQtView.h>
#include <vtkQtTableView.h>
#include <QWidget>
#include <QVTKApplication.h>
#include <QVTKWidget2.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkPolyData.h>
#include <vtkRenderer.h>
#include <QVBoxLayout>
#include <QSlider>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/NodeString.hpp>
#include <Utilities/Link.hpp>
#include <vtkMutableUndirectedGraph.h>
#include <QMap>
#include <vtkSimple2DLayoutStrategy.h>
#include <vtkGraphLayoutStrategy.h>
#include <vtkGraphLayoutView.h>
#include <vtkGraphToPolyData.h>
#include <QVTKGraphicsItem.h>
#include <vtkSimple3DCirclesStrategy.h>
#include <vtkFloatArray.h>
#include <vtkDataSetAttributes.h>
#include <vtkClustering2DLayoutStrategy.h>
#include <vtkTreeOrbitLayoutStrategy.h>
#include <vtkDynamic2DLabelMapper.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkStringArray.h>
#include <vtkProperty.h>
#include <vtkCircularLayoutStrategy.h>
#include <vtkConstrained2DLayoutStrategy.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGraphLayout.h>
#include <vtkContextTransform.h>
#include <vtkGraphItem.h>
#include <vtkContextTransform.h>
#include <vtkContextActor.h>
#include <vtkContextScene.h>
#include <QVTKWidget.h>

class GMainWindow : public QWidget
{
    Q_OBJECT
private:
    ComplexNetwork<NodeString, Link>& cn;
    vtkRenderer* renderer;
    QVTKWidget* vtk;
    vtkMutableUndirectedGraph *graph;
    vtkFloatArray *weights;

    void setVtkGraph();
public:
    explicit GMainWindow(ComplexNetwork<NodeString, Link>& cn, QWidget *parent = 0);
    virtual ~GMainWindow();

signals:

public slots:

};

#endif // GMAINWINDOW_HPP
