/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H*/

#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkConeSource.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCamera.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QFileDialog>
#include <vtkShrinkFilter.h>
#include <vtkClipDataSet.h>

#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>

#include <vtkArrowSource.h>


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void HandleChangeColourBtn();
    void HandleChangeBackgroundBtn();
    void HandleResetView();
    void HandleChangeModel();
    void HandleActionFileSave();
    void HandleActionFileOpen();


private:
    Ui::MainWindow *ui;
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    vtkSmartPointer<vtkActor> actorCube;
    vtkSmartPointer<vtkActor> actorCone;
    vtkSmartPointer<vtkActor> actorSphere;

    vtkNew<vtkShrinkFilter> shrinkCone;
    vtkNew<vtkShrinkFilter> shrinkCube;
    vtkNew<vtkShrinkFilter> shrinkSphere;

    int currentModel = 1;
    //vtkSmartPointer<vtkNamedColors> colors
};

#endif // MAINWINDOW_H
