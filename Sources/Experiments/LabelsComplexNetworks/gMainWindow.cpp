#include "gMainWindow.hpp"

GMainWindow::GMainWindow(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout;
    setLayout(l);

    resize(500,500);
    wid = new QVTKWidget2(this);
    l->addWidget(wid);

    // Sphere
      vtkSmartPointer<vtkSphereSource> sphereSource =
          vtkSmartPointer<vtkSphereSource>::New();
      sphereSource->Update();
      vtkSmartPointer<vtkPolyDataMapper> sphereMapper =
          vtkSmartPointer<vtkPolyDataMapper>::New();
      sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
      vtkSmartPointer<vtkActor> sphereActor =
          vtkSmartPointer<vtkActor>::New();
      sphereActor->SetMapper(sphereMapper);

      // Cube
//      vtkSmartPointer<vtkCubeSource> cubeSource =        vtkSmartPointer<vtkCubeSource>::New();
      /*
      vtkCubeSource *cubeSource = vtkCubeSource::New();
      cubeSource->Update();
      vtkSmartPointer<vtkPolyDataMapper> cubeMapper =
          vtkSmartPointer<vtkPolyDataMapper>::New();
      cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
      vtkSmartPointer<vtkActor> cubeActor =
          vtkSmartPointer<vtkActor>::New();
      cubeActor->SetMapper(cubeMapper);
*/
      // VTK Renderer
      vtkSmartPointer<vtkRenderer> leftRenderer =
          vtkSmartPointer<vtkRenderer>::New();
      leftRenderer->AddActor(sphereActor);

      // Add Actor to renderer
      //leftRenderer->AddActor(cubeActor);

      // VTK/Qt wedded
      this->wid->GetRenderWindow()->AddRenderer(leftRenderer);
      this->wid->GetRenderWindow()->SetSize(100,100);
      //wid->GetRenderWindow()->Render();
      leftRenderer->ResetCamera();
      //this->qvtkWidgetRight->GetRenderWindow()->AddRenderer(rightRenderer);

    //leftRenderer->ResetCamera();

      QSlider *slider = new QSlider(Qt::Horizontal);
      l->addWidget(slider);
      slider->setRange(1,100);
      wid->updateGeometry();
    QObject::connect(slider, &QSlider::sliderMoved, [=](int pos){
        double s = pos/100.;
        sphereSource->SetRadius(s);
        wid->GetRenderWindow()->Render(); });



}
