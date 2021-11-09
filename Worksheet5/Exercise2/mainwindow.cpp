#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edititemdialog.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // Your code here to connect button signals ...

    connect( ui->addButton, &QPushButton::released, this, &MainWindow::handleAddButton );
    connect( ui->editButton, &QPushButton::released, this, &MainWindow::handleEditButton );
    connect( ui->removeButton, &QPushButton::released, this, &MainWindow::handleRemoveButton );
    // Connect the statusUpdateMessage() signal to the showMessage() slot of the status bar
    connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );
}

// Example of slot implementation in mainwindow.cpp---------------------
void MainWindow::handleAddButton() {
    // This causes MainWindow to emit the signal that will then be
    // received by the statusbar's slot
    emit statusUpdateMessage( QString("Add button was clicked"), 0 );
}
// ---------------------------------------------------------------------


void MainWindow::handleRemoveButton() {
    // This causes MainWindow to emit the signal that will then be
    // received by the statusbar's slot
    emit statusUpdateMessage( QString("Remove button was clicked"), 0 );


}

void MainWindow::handleEditButton() {
    EditItemDialog dialog( this );
    StockItem item;
    emit statusUpdateMessage( QString("Edit button was clicked"), 0 );
    dialog.runDialog( item );
}

MainWindow::~MainWindow()
{
    delete ui;
}

