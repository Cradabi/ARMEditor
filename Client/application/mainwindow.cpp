#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Чтение версии программы из info.txt
    std::string filename = "../info.txt";  // Имя файла с версией программы
    std::string prog_name;

    std::ifstream file(filename);
    if (file.is_open()) {
        // Читаем первую строку
        std::getline(file, prog_name);

        // Закрываем файл
        file.close();
    } else {
        std::cout << "Не удалось открыть файл с информацией о программе" << std::endl;
        prog_name = "ARM Клиент";  // Значение по умолчанию
    }

    // Чтение имени пользователя из user.cfg
    QString username = getUserLogin("../user.cfg"); // Укажите правильный путь к user.cfg
    if (username.isEmpty()) {
        username = "Неизвестный пользователь"; // Если логин не удалось прочитать
    }

    // Устанавливаем заголовок окна
    QString windowTitle = QString("ARM Клиент %1 | Пользователь: %2").arg(QString::fromStdString(prog_name)).arg(username);
    this->setWindowTitle(windowTitle);

    // Настройка виджетов
    widget = new MyWidget();
    ui->scrollArea->setWidget(widget);
    // ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listView->setVisible(this->panel_is_visible);

    //TODO Удалить line_2 как сущность
    ui->line_2->setVisible(this->panel_is_visible);

    slot_change_panel_visibility();

    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(slot_button_close()));
    connect(ui->action_inspector, SIGNAL(triggered()), this, SLOT(slot_button_close()));
    connect(ui->action_open, SIGNAL(triggered(bool)), this, SLOT(slot_open_file_manager()));

    //connect(ui->menu_file, SIGNAL(hovered()), this, SLOT(slot_menu_hover()));

    connect(this, &MainWindow::signal_from_close_button, this, &MainWindow::slot_change_panel_visibility);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slot_button_close() {
    emit signal_from_close_button();
}

void MainWindow::slot_change_panel_visibility() {
    this->panel_is_visible = not this->panel_is_visible;
    ui->listView->setVisible(this->panel_is_visible);
    ui->line_2->setVisible(this->panel_is_visible);
    if (this->panel_is_visible) {
        ui->pushButton_close->setText(">");
    } else {
        ui->pushButton_close->setText("<");
    }
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    int px_width = this->width();
    int px_height = this->height();
    QRect rect = QRect(0, 0, px_width, px_height -
                                       50); // Почему то центральный виджет (главный контейнер) обрезает все содержимое в самом низу
    ui->verticalLayoutWidget->setGeometry(rect);
}

void MainWindow::slot_open_file_manager() {
    QString fileName = QFileDialog::getOpenFileName(this, ("Выберите файл .схема"),
                                                    "..",
                                                    ("*.схема"));
    std::string filepath = fileName.toStdString();
    std::cout << filepath << '\n';
    this->widget->draw_new_scheme(filepath);
}

// Функция для чтения логина из user.cfg
QString MainWindow::getUserLogin(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Ошибка", "Не удалось открыть файл user.cfg");
        return QString(); // Вернуть пустую строку, если файл не открылся
    }

    QString username;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("login=")) {
            username = line.mid(6).trimmed(); // Извлекаем значение после "login="
            break;
        }
    }

    file.close();
    return username;
}