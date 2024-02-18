#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow MainWindow;
    MainWindow.setFixedSize(1280,800);
    MainWindow.show();

    return app.exec();
}
