#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), emulator(new DriverEmulator(this)) {
    ui->setupUi(this);

    // Связываем кнопку старта с методом запуска сервера
    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::onStartServer);

    // Логирование из эмулятора в текстовое окно
    connect(emulator, &DriverEmulator::logMessage, this, &MainWindow::onLogMessage);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onStartServer() {
    quint16 port = ui->portSpinBox->value();

    if (!emulator->startServer(port)) {
        QMessageBox::critical(this, "Ошибка", "Не удалось запустить сервер!");
    } else {
        ui->logTextEdit->append("Сервер запущен на порту: " + QString::number(port));
    }
}

void MainWindow::onLogMessage(const QString &message) {
    ui->logTextEdit->append(message);
}