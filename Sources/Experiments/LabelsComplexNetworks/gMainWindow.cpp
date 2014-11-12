#include "gMainWindow.hpp"

GMainWindow::GMainWindow(ComplexNetwork<NodeString, Link> cn, QWidget *parent):
    QWidget(parent), cn(cn)
{
    QVBoxLayout *l = new QVBoxLayout;
    setLayout(l);

    resize(500,500);
    vtk = new QVTKWidget(this);
    l->addWidget(vtk);

    renderer = vtkRenderer::New();
    vtk->GetRenderWindow()->AddRenderer(renderer);

    setVtkGraph();
    vtkGraphLayoutView *view = vtkGraphLayoutView::New();
    vtkClustering2DLayoutStrategy *strat = vtkClustering2DLayoutStrategy::New();
    strat->SetRandomSeed(100);

    view->SetLayoutStrategy(strat);
    view->SetEdgeLabelVisibility(true);
    view->SetEdgeLabelArrayName("labels");
    view->SetEdgeLabelVisibility(true);
    view->SetEdgeLabelArrayName("weights");

    view->AddRepresentationFromInput(graph);
    vtkGraphToPolyData* graphToPoly = vtkGraphToPolyData::New();
    graphToPoly->AddInputData(graph);

    //vtk->GetRenderWindow()->AddRenderer(view->GetRenderer());
    //view->ResetCamera();

    //view->Render();

    //strat->SetGraph(graph);
    strat->SetWeightEdges(true);
    strat->SetEdgeWeightField("weights");
    strat->SetIterationsPerLayout(100);
    //strat->Layout();

    vtkGraphLayout *layout = vtkGraphLayout::New();
    layout->SetInputData(graph);
    layout->SetLayoutStrategy(strat);
    layout->Update();


    vtkGraphItem *item = vtkGraphItem::New();
    item->SetGraph(layout->GetOutput());

    vtkContextTransform *trans = vtkContextTransform::New();
    trans->AddItem(item);

    vtkContextActor *cactor = vtkContextActor::New();
    cactor->GetScene()->AddItem(trans);
/*

    vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection(graphToPoly->GetOutputPort(0));
    mapper->Update();

    vtkActor *actor = vtkActor::New();
    actor->SetMapper(mapper);

    vtkDynamic2DLabelMapper *labels = vtkDynamic2DLabelMapper::New();
    labels->SetInputConnection(graphToPoly->GetOutputPort());
    labels->SetLabelModeToLabelFieldData();
    labels->GetLabelTextProperty()->SetColor(0,0,1);
    labels->GetLabelTextProperty()->SetFontSize(40);
    labels->SetFieldDataName("labels");

    vtkActor2D* actor2 = vtkActor2D::New();
    actor2->SetMapper(labels);
    actor->GetProperty()->SetColor(0,1,0);
    actor->GetProperty()->SetOpacity(0.4);

    //renderer->AddActor(actor);
    //renderer->AddActor(actor2);*/
    renderer->AddActor(cactor);
    //item->StartLayoutAnimation(vtk->GetRenderWindow()->GetInteractor());
    vtk->GetRenderWindow()->Render();

}

void GMainWindow::setVtkGraph(){
    /*
    graph = vtkMutableUndirectedGraph::New();
    weights = vtkFloatArray::New();
    weights->SetNumberOfComponents(1);
    weights->SetName("weights");
    vtkStringArray *labels = vtkStringArray::New();
    labels->SetNumberOfComponents(1);
    labels->SetName("labels");

    QMap<Node<NodeString,Link>*, vtkIdType> map;

    for(ComplexNetwork<NodeString, Link>::node_iterator it=cn.getNodesBeginIterator(); it!=cn.getNodesEndIterator();it++){
        Node<NodeString,Link>* s = it->second;
        vtkIdType node_id = graph->AddVertex();
        map[s] = node_id;
        labels->InsertValue(node_id, s->getAttribute().text);

    }

    for(ComplexNetwork<NodeString,Link>::edge_iterator it = cn.getEdgesBeginIterator(); it!=cn.getEdgesEndIterator();it++){
        Edge<NodeString, Link>* e = it->second;
        printf("%s\t%s\t%f\n", e->getFromNode()->getAttribute().text, e->getToNode()->getAttribute().text, e->getAttribute().getWeight());
        fflush(stdout);
        vtkEdgeType edge_id = graph->AddEdge(map[e->getFromNode()], map[e->getToNode()]);
        weights->InsertValue(edge_id.Id, pow(e->getAttribute().getWeight() , 5));
        weights->InsertValue(edge_id.Id, 0.5 );
    }

    graph->GetEdgeData()->AddArray(weights);
    graph->GetVertexData()->AddArray(labels);

*/
}

GMainWindow::~GMainWindow(){
}
