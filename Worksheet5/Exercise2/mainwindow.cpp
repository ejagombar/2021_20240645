#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),ui(new Ui::MainWindow) {
    ui->setupUi(this);
    // Connect the released() signal of the addButton object to the handleAddButton slot in this object
    connect( ui->addButton, &QPushButton::released, this, &MainWindow::handleAddButton );
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleAddButton() {
    QMessageBox msgBox;
    msgBox.setText("Add button was clicked");
    msgBox.exec();
}
