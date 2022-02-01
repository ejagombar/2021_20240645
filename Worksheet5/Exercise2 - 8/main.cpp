#include "mainwindow.h"
#include <QApplication>

/** @file
* This file contains main stuff
*/
/** Main
* This is the main function
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
