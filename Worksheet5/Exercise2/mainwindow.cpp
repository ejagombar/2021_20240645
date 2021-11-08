#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // Your code here to connect button signals ...
    // Connect the statusUpdateMessage() signal to the showMessage() slot of the status bar
    connect( ui->addButton, &QPushButton::released, this, &MainWindow::handleAddButton );

    connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );
}

// Example of slot implementation in mainwindow.cpp---------------------
void MainWindow::handleAddButton() {
    // This causes MainWindow to emit the signal that will then be
    // received by the statusbar's slot
    emit statusUpdateMessage( QString("Add button was clicked"), 0 );
}
// ---------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete ui;
}

