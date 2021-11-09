#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stockitemlistmodel.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {

    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:

        void handleAddButton();
        void handleEditButton();
        void handleRemoveButton();
        void handleInsertButton();

        void handleSaveAction();


    signals:
        void statusUpdateMessage( const QString & message, int timeout );


    private:
        Ui::MainWindow *ui;
        StockItemListModel stockList;
};

#endif // MAINWINDOW_H
