#pragma once

#include <QMainWindow>
#include "lib/driver_emulator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartServer();
    void onLogMessage(const QString &message);

private:
    Ui::MainWindow *ui;
    DriverEmulator *emulator; // Объект эмулятора
};