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
class GMainWindow : public QWidget
{
    Q_OBJECT
private:
    QVTKWidget2* wid;
public:
    explicit GMainWindow(QWidget *parent = 0);

signals:

public slots:

};

#endif // GMAINWINDOW_HPP
