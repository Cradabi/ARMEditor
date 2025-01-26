#include "MainWindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
#include <fstream>

#include "MainWidget.h"
#include <nlohmann/json.hpp>


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
    widget = new MainWidget(this);
    ui->scrollArea->setWidget(widget);
    // ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setVisible(this->panel_is_visible);

    //TODO Удалить line_2 как сущность
    ui->line_2->setVisible(this->panel_is_visible);

    slot_change_panel_visibility();

    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(slot_button_close()));
    connect(ui->action_inspector, SIGNAL(triggered()), this, SLOT(slot_button_close()));
    connect(ui->action_open, SIGNAL(triggered(bool)), this, SLOT(slot_open_file_manager()));

    //connect(ui->menu_file, SIGNAL(hovered()), this, SLOT(slot_menu_hover()));

    connect(this, &MainWindow::signal_from_close_button, this, &MainWindow::slot_change_panel_visibility);
    updateListWidgetFromJson();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::slot_button_close() {
    emit signal_from_close_button();
}

void MainWindow::slot_change_panel_visibility() {
    this->panel_is_visible = not this->panel_is_visible;
    ui->listWidget->setVisible(this->panel_is_visible);
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

void MainWindow::removeOrderFromJson(const nlohmann::json& orderToRemove) {
    // Открыть JSON-файл
    QFile file("../orders_lib/orders.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл для чтения: %s", qPrintable("../orders_lib/orders.json"));
        return;
    }

    // Прочитать содержимое JSON
    QTextStream in(&file);
    QString jsonData = in.readAll();
    file.close();

    // Парсинг JSON
    nlohmann::json jsonOrders;
    try {
        jsonOrders = nlohmann::json::parse(jsonData.toStdString());
    } catch (const nlohmann::json::parse_error& e) {
        qWarning("Ошибка парсинга JSON: %s", e.what());
        return;
    }

    // Удаление соответствующего объекта
    jsonOrders.erase(
        std::remove_if(jsonOrders.begin(), jsonOrders.end(),
                       [&](const nlohmann::json& order) { return order == orderToRemove; }),
        jsonOrders.end());

    // Перезапись JSON-файла
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл для записи: %s", qPrintable("../orders_lib/orders.json"));
        return;
    }

    QTextStream out(&file);
    out << QString::fromStdString(jsonOrders.dump(4)); // С форматированием (4 пробела на отступ)
    file.close();
}

void MainWindow::updateListWidgetFromJson() {
    // Открыть JSON-файл
    QFile file("../orders_lib/orders.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл: %s", qPrintable("../orders_lib/orders.json"));
        return;
    }

    // Прочитать содержимое JSON
    QTextStream in(&file);
    QString jsonData = in.readAll();
    file.close();

    // Парсинг JSON
    nlohmann::json jsonOrders;
    try {
        jsonOrders = nlohmann::json::parse(jsonData.toStdString());
    } catch (const nlohmann::json::parse_error& e) {
        qWarning("Ошибка парсинга JSON: %s", e.what());
        return;
    }

    // Очистить listWidget перед добавлением новых данных
    ui->listWidget->clear();

    // Обработка JSON
    for (const auto& order : jsonOrders) {
        // Извлечение данных из JSON
        QString controlPoint = QString::fromStdString(order.value("control_point", ""));
        QString dispatcher = QString::fromStdString(order.value("dispatcher", ""));
        QString object = QString::fromStdString(order.value("object", ""));
        int operationType = order.value("operation_type", 0);
        QString timestamp = QString::fromStdString(order.value("timestamp", ""));

        // Создание виджета для отображения данных
        QWidget* orderWidget = new QWidget(ui->listWidget);
        QVBoxLayout* layout = new QVBoxLayout(orderWidget);
        layout->setContentsMargins(5, 5, 5, 5);

        QString _operationType;
        if (operationType == 0) {
            _operationType = "Отключить";
        } else {
            _operationType = "Включить";
        }

        QString orderInfo = QString("На %1\n%4 %3\nВремя: %5")
                                .arg(controlPoint, object)
                                .arg(_operationType)
                                .arg(timestamp);

        QLabel* label = new QLabel(orderInfo, orderWidget);
        QPushButton* deleteButton = new QPushButton("Отменить", orderWidget);

        layout->addWidget(label);
        layout->addWidget(deleteButton);
        orderWidget->setLayout(layout);

        // Добавить виджет в QListWidget
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        item->setSizeHint(orderWidget->sizeHint());
        ui->listWidget->addItem(item);
        ui->listWidget->setItemWidget(item, orderWidget);

        // Связать кнопку удаления с функцией удаления
        connect(deleteButton, &QPushButton::clicked, this, [=]() {
            // Удалить элемент из QListWidget
            int row = ui->listWidget->row(item);
            delete ui->listWidget->takeItem(row);

            // Удалить элемент из JSON
            removeOrderFromJson(order);
        });
    }
    setupConnections();
}

void MainWindow::setupConnections() {
    connect(ui->listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
}

void MainWindow::onItemDoubleClicked(QListWidgetItem* item) {
    // Получить виджет элемента
    QWidget* orderWidget = ui->listWidget->itemWidget(item);
    QLabel* label = orderWidget->findChild<QLabel*>();
    QString orderInfo = label ? label->text() : "Нет данных";

    // Создаем диалоговое окно
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Детали приказа");
    dialog->resize(400, 300);

    // Создаем лейаут для диалогового окна
    QVBoxLayout* dialogLayout = new QVBoxLayout(dialog);

    // Отображаем информацию о приказе
    QLabel* infoLabel = new QLabel(orderInfo, dialog);
    dialogLayout->addWidget(infoLabel);

    // Добавляем кнопки
    QPushButton* executeButton = new QPushButton("Выполнить", dialog);
    QPushButton* viaRUButton = new QPushButton("Через РУ", dialog);
    QPushButton* cancelButton = new QPushButton("Отменить", dialog);

    dialogLayout->addWidget(executeButton);
    dialogLayout->addWidget(viaRUButton);
    dialogLayout->addWidget(cancelButton);

    // Устанавливаем лейаут для диалога
    dialog->setLayout(dialogLayout);

    // Связываем кнопки с действиями
    connect(executeButton, &QPushButton::clicked, dialog, [=]() {
        qDebug() << "Выполнить: " << orderInfo;
        dialog->accept();
    });

    connect(viaRUButton, &QPushButton::clicked, dialog, [=]() {
        qDebug() << "Через РУ: " << orderInfo;
        dialog->accept();
    });

    connect(cancelButton, &QPushButton::clicked, this, [=]() {
            // Удалить элемент из QListWidget
            int row = ui->listWidget->row(item);
            delete ui->listWidget->takeItem(row);

            // Удалить элемент из JSON
            // removeOrderFromJson(order);
        });

    // Показываем диалог
    dialog->exec();
}
