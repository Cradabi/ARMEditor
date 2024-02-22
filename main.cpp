#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow MainWindow;

    MainWindow.setWindowState(Qt::WindowMaximized);
    MainWindow.show();

    return app.exec();
}
