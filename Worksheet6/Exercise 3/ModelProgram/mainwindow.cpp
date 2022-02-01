#include "mainwindow.h"
#include "./ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // standard call to setup Qt UI (same as previously)
    ui->setupUi( this );
    connect( ui->ChangeColourBtn, &QPushButton::released, this, &MainWindow::HandleChangeColourBtn );
    connect( ui->ChangeBackgroundBtn, &QPushButton::released, this, &MainWindow::HandleChangeBackgroundBtn );
    connect( ui->ResetViewBtn, &QPushButton::released, this, &MainWindow::HandleResetView );
    connect( ui->actionFileSave, &QAction::triggered, this, &MainWindow::HandleActionFileSave );
    connect( ui->actionFileOpen, &QAction::triggered, this, &MainWindow::HandleActionFileOpen );
    //connect( ui->ChangeModelBtn, &QPushButton::released, this, &MainWindow::HandleChangeModel );

    // Now need to create a VTK render window and link it to the QtVTK widget

    ui->qvtkWidget->QVTKOpenGLStereoWidget::setRenderWindow( renderWindow );			// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator

    // Now use the VTK libraries to render something. To start with you can copy-paste the cube example code, there are comments to show where the code must be modified.
    //--------------------------------------------- Code From Example 1 --------------------------------------------------------------------------


    // Create a cube using a vtkCubeSource
    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

    // Create a mapper that will hold the cube's geometry in a format suitable for rendering
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection( cubeSource->GetOutputPort() );

    // Create an actor that is used to set the cube's properties for rendering and place it in the window
    actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->EdgeVisibilityOn();

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    actor->GetProperty()->SetColor( colors->GetColor3d("Blue").GetData() );

    // Create a renderer, and render window
    renderer = vtkSmartPointer<vtkRenderer>::New();
    //vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
    ui->qvtkWidget->QVTKOpenGLStereoWidget::renderWindow()->AddRenderer( renderer );	// ###### ask the QtVTKOpenGLWidget for its renderWindow ######
    // Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######
    //vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );

    // Add the actor to the scene
    renderer->AddActor(actor);
    renderer->SetBackground( colors->GetColor3d("Silver").GetData() );

    // Setup the renderers's camera
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();

    // Render and interact
    //renderWindow->Render();					// ###### Not needed with Qt ######
    //renderWindowInteractor->Start();			// ###### Not needed with Qt ######
    //--------------------------------------------- /Code From Example 1 -------------------------------------------------------------------------*/
}


void MainWindow::HandleChangeColourBtn()
{
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    actor->GetProperty()->SetColor( colors->GetColor3d("Green").GetData() );
    renderWindow->Render();
}

void MainWindow::HandleChangeBackgroundBtn()
{
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    renderer->SetBackground( colors->GetColor3d("ffffff").GetData() );
    renderWindow->Render();
}

void MainWindow::HandleResetView()
{
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderWindow->Render();
}

void MainWindow::HandleChangeModel()
{

    // Create a cube using a vtkCubeSource
    vtkSmartPointer<vtkConeSource> cubeSource = vtkSmartPointer<vtkConeSource>::New();

    // Create a mapper that will hold the cube's geometry in a format suitable for rendering
    vtkSmartPointer<vtkDataSetMapper> mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputConnection( cubeSource->GetOutputPort() );

    // Create an actor that is used to set the cube's properties for rendering and place it in the window
    actor->SetMapper(mapper);

    actor->GetProperty()->EdgeVisibilityOn();

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();
    actor->GetProperty()->SetColor( colors->GetColor3d("ffffff").GetData() );
    renderer->AddActor(actor);
    renderWindow->Render();
}

void MainWindow::HandleActionFileOpen()
{

    QFileDialog dialog(this);
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open STL File"), "./", tr("STL Files(*.stl)"));
    QByteArray ba = fileName.toLocal8Bit();
    const char *c_str2 = ba.data();


    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkSTLReader> reader;
      reader->SetFileName(c_str2);
      reader->Update();

      // Visualize
      vtkNew<vtkPolyDataMapper> mapper;
      mapper->SetInputConnection(reader->GetOutputPort());

      vtkNew<vtkActor> actor;
      actor->SetMapper(mapper);
      actor->GetProperty()->SetDiffuse(0.8);
      actor->GetProperty()->SetDiffuseColor(
          colors->GetColor3d("LightSteelBlue").GetData());
      actor->GetProperty()->SetSpecular(0.3);
      actor->GetProperty()->SetSpecularPower(60.0);

      vtkNew<vtkRenderer> renderer;
      vtkNew<vtkRenderWindow> renderWindow;
      renderWindow->AddRenderer(renderer);
      renderWindow->SetWindowName("ReadSTL");

      vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
      renderWindowInteractor->SetRenderWindow(renderWindow);

      renderer->AddActor(actor);
      renderer->SetBackground(colors->GetColor3d("DarkOliveGreen").GetData());

      renderWindow->Render();
      renderWindowInteractor->Start();

}


void MainWindow::HandleActionFileSave()
{
    QFileDialog dialog(this);
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save STL File"), "./", tr("STL Files(*.stl)"));
}



MainWindow::~MainWindow()
{
    delete ui;
}
