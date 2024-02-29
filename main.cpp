#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow MainWindow;

    MainWindow.setWindowState(Qt::WindowMaximized);
    MainWindow.setMinimumSize(400, 400);
    MainWindow.show();

    return app.exec();
}
