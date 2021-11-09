// mainwindow.cpp ------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "stockitem.h"
#include "edititemdialog.h"
#include <QMessageBox>
#include "stockitemlistmodel.h"
#include <QFileDialog>




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    // Link the ListModel to the ListView
    ui->listView->setModel( &stockList );
    // Tell this list view to only accept single selections
    ui->listView->setSelectionBehavior( QAbstractItemView::SelectItems );
    // Connect the released() signal of the addButton object to the handleAddButton slot in this object

    connect( ui->addButton, &QPushButton::released, this, &MainWindow::handleAddButton );
    connect( ui->editButton, &QPushButton::released, this, &MainWindow::handleEditButton );
    connect( ui->removeButton, &QPushButton::released, this, &MainWindow::handleRemoveButton );
    connect( ui->insertButton, &QPushButton::released, this, &MainWindow::handleInsertButton );
    connect( ui->saveAction, &QAction::triggered, this, &MainWindow::handleSaveAction );
    connect( this, &MainWindow::statusUpdateMessage, ui->statusBar, &QStatusBar::showMessage );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleInsertButton() {
    StockItem item;
    EditItemDialog dialog( this );
    QModelIndexList selectedList;
    selectedList = ui->listView->selectionModel()->selectedIndexes();

    if( selectedList.length() == 1 ) {
        // selectedList is a list of all selected items in the listView. Since we set its
        // behaviour to single selection, were only interested in the first selecteded item.
        stockList.insertItem(item,selectedList[0]);
        emit statusUpdateMessage( QString("Insert button was clicked"), 0 );
    } else {
        emit statusUpdateMessage( QString("No item selected to remove!"), 0 );
    }
}

void MainWindow::handleAddButton() {
    StockItem item;
    stockList.addItem( item );
    emit statusUpdateMessage( QString("Add button was clicked"), 0 );
}

void MainWindow::handleEditButton() {
    EditItemDialog dialog( this );
    QModelIndexList selectedList;
    selectedList = ui->listView->selectionModel()->selectedIndexes();
    if( selectedList.length() == 1 ) {
        // selectedList is a list of all selected items in the listView. Since we set its
        // behaviour to single selection, were only interested in the first selecteded item.
        StockItem item = stockList.getItem( selectedList[0] );
    if( dialog.runDialog( item ) ) {
        // user clicked ok, need to update item in list...
        stockList.setItem( item, selectedList[0] );
    }
    } else {
        emit statusUpdateMessage( QString("No item selected to edit!"), 0 );
    }
}

void MainWindow::handleRemoveButton() {

    EditItemDialog dialog( this );
    QModelIndexList selectedList;
    selectedList = ui->listView->selectionModel()->selectedIndexes();

    if( selectedList.length() == 1 ) {
        // selectedList is a list of all selected items in the listView. Since we set its
        // behaviour to single selection, were only interested in the first selecteded item.
        stockList.removeItem(selectedList[0]);
    } else {
        emit statusUpdateMessage( QString("No item selected to remove!"), 0 );
    }

}

void MainWindow::handleSaveAction() {
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();
    emit statusUpdateMessage( QString("saved!!!!"), 0 );
}
// ---------------------------------------------------------------------


