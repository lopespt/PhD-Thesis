#ifndef COMPLEXNETWORKVIEWERWIDGET_HPP
#define COMPLEXNETWORKVIEWERWIDGET_HPP

#include <QWidget>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <FeatureExtractors/FeatureAbstract.hpp>
#include <QVTKWidget2.h>
#include <QVTKWidget.h>
#include <QVBoxLayout>
#include <vtkRenderer.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkGraphMapper.h>
#include <vtkSmartPointer.h>
#include <vtkCommunity2DLayoutStrategy.h>
#include <vtkClustering2DLayoutStrategy.h>
#include <vtkIntArray.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKInteractor.h>
#include <vtkStringArray.h>
#include <vtkGenericRenderWindowInteractor.h>
#include <vtkInteractorStyleFlight.h>
#include <vtkGraphLayout.h>
#include <vtkGraphToPolyData.h>
#include <vtkGraphToGlyphs.h>
#include <vtkPolyDataMapper.h>
#include <vtkGlyph3D.h>
#include <vtkCubeSource.h>
#include <vtkDynamic2DLabelMapper.h>
#include <vtkActor2D.h>
#include <vtkColorTransferFunction.h>
#include <vtkRenderedGraphRepresentation.h>
#include <Utilities/FeaturesComplexNetwork/Link.hpp>
#include <vtkFloatArray.h>
#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>

class ComplexNetworkViewerWidget : public QWidget {
Q_OBJECT
private:
    FeaturesComplexNetwork *cn;
    QVTKWidget2 *vtkWidget;
    vtkRenderer *vRenderer;
    vtkGraphLayoutView *viewer;
    vtkMutableUndirectedGraph *graph;
    QVTKInteractor *interactor;

    void createVtkPipeline();

public:
    explicit ComplexNetworkViewerWidget(QWidget *parent = 0);

    void setComplexNetwork(FeaturesComplexNetwork &cn);

    virtual ~ComplexNetworkViewerWidget();

signals:

public slots:

};

#endif // COMPLEXNETWORKVIEWERWIDGET_HPP
