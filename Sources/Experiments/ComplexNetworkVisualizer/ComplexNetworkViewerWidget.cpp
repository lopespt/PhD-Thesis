#include "ComplexNetworkViewerWidget.hpp"
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkDataSetAttributes.h>
#include <QMap>
#include <vtkProperty.h>
#include <vtkProperty2D.h>
#include <vtkTextProperty.h>
ComplexNetworkViewerWidget::ComplexNetworkViewerWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* lay = new QVBoxLayout;
    this->setLayout(lay);
    this->vtkWidget = new QVTKWidget2;
    this->vRenderer = vtkRenderer::New();
    this->viewer = vtkGraphLayoutView::New();
    this->graph = vtkMutableUndirectedGraph::New();
    //vtkWidget->SetRenderWindow(vtkGenericOpenGLRenderWindow::New());
    vtkWidget->GetRenderWindow()->AddRenderer(vRenderer);
    lay->addWidget(vtkWidget);
    vRenderer->SetBackground(0.3,0.4,0.5);
}

void ComplexNetworkViewerWidget::setComplexNetwork(ComplexNetwork<NodeString, Link> &cn){
    this->cn = &cn;
    QMap<Node<NodeString, Link>*, vtkIdType> vertices;
    vtkFloatArray *array = vtkFloatArray::New();
    vtkStringArray *array2 = vtkStringArray::New();
    array->SetName("pesos");
    array2->SetName("nomes");
    for(ComplexNetwork<NodeString, Link>::node_iterator it = this->cn->getNodesBeginIterator(); it!=this->cn->getNodesEndIterator(); it++){
        vtkIdType node_id = this->graph->AddVertex();
        vertices[it->second] = node_id;
        array2->InsertValue(node_id, it->second->getAttribute().text);
    }

    for(ComplexNetwork<NodeString, Link>::edge_iterator it = this->cn->getEdgesBeginIterator(); it!=this->cn->getEdgesEndIterator(); it++){
        Edge<NodeString, Link> *edge;
        edge=it->second;
        vtkEdgeType edgeId = this->graph->AddEdge(vertices[edge->getFromNode()], vertices[edge->getToNode()]);
        array->InsertValue(edgeId.Id, edge->getAttribute().getWeight());
    }
    this->graph->GetEdgeData()->AddArray(array);
    this->graph->GetVertexData()->AddArray(array2);

   createVtkPipeline();
   this->vRenderer->ResetCamera();
   this->vtkWidget->GetRenderWindow()->GetInteractor()->EnableRenderOn();
   this->vtkWidget->GetRenderWindow()->Render();
   //this->viewer->SetInteractorStyle(vtkInteractorStyleFlight::New());
   //this->viewer->GetInteractor()->Start();
   //this->viewer->GetInteractor()->Start();
   //this->vRenderer->Render();
}

void ComplexNetworkViewerWidget::createVtkPipeline(){
    //vtkGraphMapper* mapper=vtkGraphMapper::New();
    vtkGraphToPolyData *edgesPoly = vtkGraphToPolyData::New();
    vtkPolyDataMapper *edgesMapper = vtkPolyDataMapper::New();
    vtkPolyDataMapper *nodesMapper = vtkPolyDataMapper::New();
    vtkGlyph3D *glyph = vtkGlyph3D::New();

    vtkGraphLayout *layout = vtkGraphLayout::New();

    layout->SetInputData(graph);
    vtkClustering2DLayoutStrategy *lay = vtkClustering2DLayoutStrategy::New();
    lay->SetRandomSeed(1000);
    lay->SetGraph(this->graph);
    //mapper->SetInputData(this->graph);
    layout->SetLayoutStrategy(lay);
    lay->SetMaxNumberOfIterations(10000);
    lay->SetWeightEdges(true);
    lay->SetEdgeWeightField("pesos");
    lay->Layout();
    layout->Update();

    //Edges polydata
    edgesPoly->SetInputConnection(layout->GetOutputPort());

    edgesMapper->SetInputConnection(edgesPoly->GetOutputPort());
    vtkActor *actor = vtkActor::New();
    actor->SetMapper(edgesMapper);
    vtkColorTransferFunction *lc = vtkColorTransferFunction::New();
    lc->AddHSVPoint(0,0,1,1);
    lc->AddHSVPoint(1000,1,1,1);
    edgesMapper->SetColorModeToMapScalars();
    edgesMapper->SetLookupTable(lc);
    actor->GetProperty()->SetOpacity(0.01);
    actor->GetProperty()->SetColor(0.4,0.6,0);
    //edgesMapper->SetScalarModeToDefault();


    //Nodes
    glyph->SetInputConnection(0, edgesPoly->GetOutputPort());
    vtkCubeSource *cube = vtkCubeSource::New();
    cube->SetXLength(0.1);
    cube->SetYLength(0.1);
    cube->SetZLength(0.1);
    glyph->SetInputConnection(1, cube->GetOutputPort());
    nodesMapper->SetInputConnection(glyph->GetOutputPort());
    //nodesMapper->SetScalarModeToUseCellFieldData();


    //Nodes Labels
    vtkDynamic2DLabelMapper *nodeLabels = vtkDynamic2DLabelMapper::New();
    nodeLabels->SetInputConnection(edgesPoly->GetOutputPort());
    nodeLabels->SetLabelModeToLabelFieldData();
    nodeLabels->SetFieldDataName("nomes");
    nodeLabels->GetLabelTextProperty()->SetFontSize(30);


    vtkActor *actor2 = vtkActor::New();
    actor2->SetMapper(nodesMapper);
    actor2->GetProperty()->SetColor(1,1,0);

    vtkActor2D *actor3 = vtkActor2D::New();
    actor3->SetMapper(nodeLabels);

    /*
    viewer->AddRepresentationFromInput(this->graph);
    viewer->GetRenderer()->SetAmbient(0.3,0.4,0.5);
    viewer->SetLayoutStrategy(lay);
    viewer->SetEdgeLabelVisibility(true);
    viewer->SetEdgeLabelArrayName("pesos");
    viewer->SetRenderWindow(vtkWidget->GetRenderWindow());
    viewer->ResetCamera();
    viewer->SetVertexLabelVisibility(true);
    viewer->SetVertexLabelArrayName("nomes");
*/
    vRenderer->AddActor(actor);
    vRenderer->AddActor(actor2);
    vRenderer->AddActor2D(actor3);
}

ComplexNetworkViewerWidget::~ComplexNetworkViewerWidget(){
    this->vRenderer->Delete();
    this->graph->Delete();
    this->viewer->Delete();
}
