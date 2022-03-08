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
    connect( ui->ChangeModelBtn, &QPushButton::released, this, &MainWindow::HandleChangeModel );
    connect( ui->ShrinkCheckBox, &QCheckBox::stateChanged, this, &MainWindow::HandleCheckBox );
    connect( ui->ClipCheckBox, &QCheckBox::stateChanged, this, &MainWindow::HandleCheckBox2 );

    // Now need to create a VTK render window and link it to the QtVTK widget

    ui->qvtkWidget->QVTKOpenGLStereoWidget::setRenderWindow( renderWindow );			// note that vtkWidget is the name I gave to my QtVTKOpenGLWidget in Qt creator

    // Now use the VTK libraries to render something. To start with you can copy-paste the cube example code, there are comments to show where the code must be modified.
    //--------------------------------------------- Code From Example 1 --------------------------------------------------------------------------


    // Create a cube using a vtkCubeSource
    vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();
    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();

    /*vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();

    light->SetLightTypeToSceneLight();
    light->SetPosition( 8, 8, 15 );
    light->SetPositional( true );
    light->SetConeAngle( 10 );
    light->SetFocalPoint( 0, 0, 0 );
    light->SetDiffuseColor( 1, 1, 1 );
    light->SetAmbientColor( 1, 1, 1 );
    light->SetSpecularColor( 1, 1, 1 );
    light->SetIntensity( 0.7 );*/

    planeLeft = vtkSmartPointer<vtkPlane>::New();
    planeLeft->SetOrigin(-99.0, -100.0, -100.0);
    planeLeft->SetNormal(-1.0, 1.0, 0.0);

    CubeClip = vtkSmartPointer<vtkClipDataSet>::New();
    ConeClip = vtkSmartPointer<vtkClipDataSet>::New();
    SphereClip = vtkSmartPointer<vtkClipDataSet>::New();

    CubeClip->SetInputConnection( cubeSource->GetOutputPort() );
    ConeClip->SetInputConnection( coneSource->GetOutputPort() ) ;
    SphereClip->SetInputConnection( sphereSource->GetOutputPort() ) ;


    CubeClip->SetClipFunction( planeLeft.Get() );
    ConeClip->SetClipFunction( planeLeft.Get() );
    SphereClip->SetClipFunction( planeLeft.Get() );


    shrinkCube->SetInputConnection(CubeClip->GetOutputPort());
    shrinkCone->SetInputConnection(ConeClip->GetOutputPort());
    shrinkSphere->SetInputConnection(SphereClip->GetOutputPort());

    shrinkSphere->SetShrinkFactor(1);
    shrinkCone->SetShrinkFactor(1);
    shrinkCube->SetShrinkFactor(1);

    // Create a mapper that will hold the cube's geometry in a format suitable for rendering
    vtkSmartPointer<vtkDataSetMapper> cubeMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkDataSetMapper> coneMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    vtkSmartPointer<vtkDataSetMapper> sphereMapper = vtkSmartPointer<vtkDataSetMapper>::New();

    cubeMapper->SetInputConnection( shrinkCube->GetOutputPort() );
    coneMapper->SetInputConnection( shrinkCone->GetOutputPort() );
    sphereMapper->SetInputConnection( shrinkSphere->GetOutputPort() );

    actorCube = vtkSmartPointer<vtkActor>::New();
    actorCone = vtkSmartPointer<vtkActor>::New();
    actorSphere = vtkSmartPointer<vtkActor>::New();

    actorCube->SetMapper(cubeMapper);
    actorCone->SetMapper(coneMapper);
    actorSphere->SetMapper(sphereMapper);

    actorCone->GetProperty()->EdgeVisibilityOn();
    actorCube->GetProperty()->EdgeVisibilityOn();
    actorSphere->GetProperty()->EdgeVisibilityOn();

    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    actorCube->GetProperty()->SetColor( colors->GetColor3d("Blue").GetData() );
   // actorCone->GetProperty()->SetColor( colors->GetColor3d("Red").GetData() );
   // actorSphere->GetProperty()->SetColor( colors->GetColor3d("White").GetData() );

    //vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();		// ###### We've already created the renderWindow this time ######
    ui->qvtkWidget->QVTKOpenGLStereoWidget::renderWindow()->AddRenderer( renderer );	// ###### ask the QtVTKOpenGLWidget for its renderWindow ######
    // Link a renderWindowInteractor to the renderer (this allows you to capture mouse movements etc)  ###### Not needed with Qt ######
    //vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //renderWindowInteractor->SetRenderWindow( ui->vtkWidget->GetRenderWindow() );

    // Add the actor to the scene
    //renderer->AddActor(actorCone);
    renderer->AddActor(actorCube);
    //renderer->AddActor(actorSphere);

    //renderer->AddLight( light );

    renderer->SetBackground( colors->GetColor3d("Orange").GetData() );

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

    QColor ColourDialog = QColorDialog::getColor();
    float Red,Green,Blue = 0;
    Red=ColourDialog.redF();
    Green=ColourDialog.greenF();
    Blue=ColourDialog.blueF();

    actorCube->GetProperty()->SetColor( Red,Green,Blue  );
    actorCone->GetProperty()->SetColor( Red,Green,Blue  );
    actorSphere->GetProperty()->SetColor(  Red,Green,Blue  );
    renderWindow->Render();

}

void MainWindow::HandleChangeBackgroundBtn()
{
    QColor ColourDialog = QColorDialog::getColor();
    float Red,Green,Blue = 0;
    Red=ColourDialog.redF();
    Green=ColourDialog.greenF();
    Blue=ColourDialog.blueF();

    renderer->SetBackground( Red,Green,Blue );
    renderWindow->Render();
}

void MainWindow::HandleResetView()
{
    renderer->ResetCamera();
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    renderer->ResetCameraClippingRange();
    renderWindow->Render();

}

void MainWindow::HandleCheckBox()
{
    if (currentShrink == 0)
    {
        shrinkSphere->SetShrinkFactor(.7);
        shrinkCone->SetShrinkFactor(.7);
        shrinkCube->SetShrinkFactor(.7);
        currentShrink = 1;
    }
    else if (currentShrink == 1)
    {
        shrinkSphere->SetShrinkFactor(1);
        shrinkCone->SetShrinkFactor(1);
        shrinkCube->SetShrinkFactor(1);
        currentShrink = 0;
    }


    shrinkSphere -> Update();
    shrinkCone -> Update();
    shrinkCube -> Update();

    ConeClip -> Update();
    CubeClip -> Update();
    SphereClip -> Update();

    renderWindow->Render();

}

void MainWindow::HandleCheckBox2()
{
    if (currentClip == 1)
    {
        planeLeft->SetOrigin(100.0, 100.0, 100.0);
        planeLeft->SetNormal(-1.0, 0.0, 0.0);
        currentClip = 0;
    }
    else if (currentClip == 0)
    {
        planeLeft->SetOrigin(0.0, 0.0, 0.0);
        planeLeft->SetNormal(-1.0, 0.0, 0.0);
        currentClip = 1;
    }

    ConeClip -> Update();
    CubeClip -> Update();
    SphereClip -> Update();


    shrinkSphere -> Update();
    shrinkCone -> Update();
    shrinkCube -> Update();

    renderWindow->Render();
}

void MainWindow::HandleChangeModel()
{
    renderer ->RemoveAllViewProps();
    if (currentModel == 3){
        renderer->AddActor(actorCube);
        currentModel = 1;
    }

    else if (currentModel == 2){
        renderer->AddActor(actorCone);
        currentModel = 3;
    }

    else if (currentModel == 1){
        renderer->AddActor(actorSphere);
        currentModel = 2;
    }

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

      vtkNew<vtkActor> actor;



      shrinkActor->SetInputConnection(reader->GetOutputPort());
      shrinkActor->SetShrinkFactor(1);

      mapper->SetInputConnection( reader->GetOutputPort() );

      actor->SetMapper(mapper);
      actor->GetProperty()->SetDiffuse(0.8);
      actor->GetProperty()->SetDiffuseColor(
      colors->GetColor3d("LightSteelBlue").GetData());
      actor->GetProperty()->SetSpecular(0.3);
      actor->GetProperty()->SetSpecularPower(60.0);


      //vtkNew<vtkRenderWindowInteractor> renderWindowInteractor;
      //renderWindowInteractor->SetRenderWindow(renderWindow);

      renderer->AddActor(actor);

      renderer->RemoveActor(actorCone);
      renderer->RemoveActor(actorSphere);
      renderer->RemoveActor(actorCube);

      renderWindow->Render();
     // renderWindowInteractor->Start();

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
