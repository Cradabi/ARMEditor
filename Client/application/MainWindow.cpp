#include "MainWindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>
#include <fstream>

#include "MainWidget.h"
#include <nlohmann/json.hpp>
#include <sys/stat.h>

#include "OrderWidget.h"


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Чтение версии программы из info.txt
    std::string filename = "../info.txt"; // Имя файла с версией программы
    std::string prog_name;

    std::ifstream file(filename);
    if (file.is_open()) {
        // Читаем первую строку
        std::getline(file, prog_name);

        // Закрываем файл
        file.close();
    } else {
        std::cout << "Не удалось открыть файл с информацией о программе" << std::endl;
        prog_name = "ARM Клиент"; // Значение по умолчанию
    }

    // Чтение имени пользователя из user.cfg
    QString username = getUserLogin("../user.cfg"); // Укажите правильный путь к user.cfg
    if (username.isEmpty()) {
        username = "Неизвестный пользователь"; // Если логин не удалось прочитать
    }

    // Устанавливаем заголовок окна
    QString windowTitle = QString("ARM Клиент %1 | Диспетчер: %2")
            .arg(QString::fromStdString(prog_name))
            .arg(username);
    this->setWindowTitle(windowTitle);

    // Чтение максимального ID приказа
    max_order_id = readMaxOrderId("../orders_lib/orders.json");

    // Настройка основного виджета
    widget = new MainWidget(this);  // Основной виджет для отображения чего-то другого
    ui->scrollArea->setWidget(widget);  // Устанавливаем виджет в scrollArea

    // Настройка контейнера для приказов
    listLayout = new QVBoxLayout();  // QVBoxLayout для хранения виджетов приказов
    QWidget *listContainer = new QWidget();  // Контейнер для layout
    listContainer->setLayout(listLayout);

    // Устанавливаем контейнер в scrollArea
    ui->ordersScrollArea->setWidget(listContainer);
    ui->ordersScrollArea->setWidgetResizable(true);  // Делаем, чтобы контейнер автоматически подстраивался под размер списка

    ui->line_2->setVisible(this->panel_is_visible);

    // Изначально скрываем панель с приказами
    slot_change_panel_visibility();

    // Связываем сигналы с кнопками и действиями интерфейса
    connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(slot_button_close()));
    connect(ui->action_inspector, SIGNAL(triggered()), this, SLOT(slot_button_close()));
    connect(ui->action_open, SIGNAL(triggered(bool)), this, SLOT(slot_open_file_manager()));

    // Настройка клиента и потока для обработки сетевых операций
    clientThread = new QThread(this);
    client = new arm_client();
    client->moveToThread(clientThread);

    connect(clientThread, &QThread::started, client, [=]() {
        client->connectToServer("localhost", 3011);
    });
    connect(client, &arm_client::messageReceived, this, &MainWindow::ReadMessageReceivedtest);
    connect(this, &MainWindow::sendCommannd, client, &arm_client::sendCommand);
    connect(client, &arm_client::errorOccurred, this, [](const QString &error) {
        qDebug() << "Ошибка соединения:" << error;
    });

    // Добавляем обработку завершения потока
    connect(clientThread, &QThread::finished, client, &arm_client::deleteLater);
    connect(clientThread, &QThread::finished, clientThread, &QThread::deleteLater);

    clientThread->start();

    // Связываем сигнал от кнопки закрытия панели с функцией изменения видимости панели
    connect(this, &MainWindow::signal_from_close_button, this, &MainWindow::slot_change_panel_visibility);

    // Обновляем список приказов
    updateListWidgetFromJson();
}

MainWindow::~MainWindow() {
    if (clientThread) {
        clientThread->quit();
        clientThread->wait();
    }
    delete ui;
}

void MainWindow::ReadMessageReceivedtest(const QString &message) {
    // Обработка входящего сообщения
    qDebug() << "Получено сообщение от сервера:" << message;
    // Можно добавить дополнительную логику обработки сообщений
}

void MainWindow::slot_button_close() {
    emit signal_from_close_button();
}

void MainWindow::slot_change_panel_visibility() {
    this->panel_is_visible = not this->panel_is_visible;
    ui->ordersScrollArea->setVisible(this->panel_is_visible);
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
                                       50);
    // Почему то центральный виджет (главный контейнер) обрезает все содержимое в самом низу
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

void MainWindow::updateListWidgetFromJson() {
    QFile file("../orders_lib/orders.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл: %s", qPrintable("../orders_lib/orders.json"));
        return;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning("Ошибка парсинга JSON: %s", qPrintable(parseError.errorString()));
        return;
    }

    QJsonArray jsonOrders = jsonDoc.array();

    QLayoutItem *child;
    while ((child = listLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    for (const QJsonValue &orderValue: jsonOrders) {
        QJsonObject order = orderValue.toObject();
        QString controlPoint = order.value("control_point").toString();
        QString dispatcher = order.value("dispatcher").toString();
        QString object = order.value("object").toString();
        int operationType = order.value("operation_type").toInt(0);
        QString timestamp = order.value("timestamp").toString();
        int id = order.value("id").toInt(0);
        int object_id = order.value("object_id").toInt(0);

        OrderWidget *orderWidget = new OrderWidget(id);
        orderWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        QVBoxLayout *layout = new QVBoxLayout(orderWidget);
        layout->setContentsMargins(5, 5, 5, 5);

        QString _operationType = (operationType == 0) ? "Включить" : "Отключить";
        QString orderInfo = QString("Приказ №%6\nНа %1\n%4 %3\nВремя: %5")
                .arg(controlPoint, object)
                .arg(_operationType)
                .arg(timestamp)
                .arg(id);

        QLabel *label = new QLabel(orderInfo, orderWidget);
        QPushButton *deleteButton = new QPushButton("Отменить", orderWidget);

        layout->addWidget(label);
        layout->addWidget(deleteButton);
        orderWidget->setLayout(layout);

        listLayout->addWidget(orderWidget);

        connect(deleteButton, &QPushButton::clicked, this, [=]() {
            removeOrderFromJson(id);
            updateListWidgetFromJson();
        });

        connect(orderWidget, &OrderWidget::clicked, this, [=](int orderId) {
            QJsonObject selectedOrder;
            for (const QJsonValue &orderValue : jsonOrders) {
                if (orderValue.toObject().value("id").toInt() == orderId) {
                    selectedOrder = orderValue.toObject();
                    break;
                }
            }
            onOrderWidgetClicked(selectedOrder);
        });
    }

    listLayout->setAlignment(Qt::AlignTop);
    ui->ordersScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Устанавливаем фиксированную ширину, если нет заказов, иначе обновляем
    QTimer::singleShot(0, this, [this, jsonOrders]() {
        int scrollBarWidth = ui->ordersScrollArea->verticalScrollBar()->sizeHint().width();
        int frameWidth = ui->ordersScrollArea->frameWidth() * 2;
        int contentWidth = listLayout->sizeHint().width();
        int desiredWidth = (jsonOrders.isEmpty()) ? 200 : (contentWidth + scrollBarWidth + frameWidth);
        ui->ordersScrollArea->setFixedWidth(desiredWidth);
    });
}

void MainWindow::removeOrderFromJson(int orderIdToRemove) {
    QFile file("../orders_lib/orders.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл для удаления");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning("Ошибка парсинга JSON: %s", qPrintable(parseError.errorString()));
        return;
    }

    QJsonArray jsonOrders = jsonDoc.array();  // Получаем массив приказов

    // Ищем и удаляем приказ по id
    for (int i = 0; i < jsonOrders.size(); ++i) {
        QJsonObject order = jsonOrders[i].toObject();
        if (order.value("id").toInt() == orderIdToRemove) {
            jsonOrders.removeAt(i);
            break;
        }
    }

    // Записываем обновленный JSON обратно в файл
    QJsonDocument updatedDoc(jsonOrders);
    QFile outFile("../orders_lib/orders.json");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning("Не удалось открыть файл для записи");
        return;
    }

    outFile.write(updatedDoc.toJson(QJsonDocument::Indented));  // Записываем с отступами
    outFile.close();
}

void MainWindow::onOrderWidgetClicked(const QJsonObject &order) {
    // Создаём диалоговое окно
    QDialog *detailsDialog = new QDialog(this);
    detailsDialog->setWindowTitle(QString("Приказ №%1").arg(order.value("id").toInt()));
    detailsDialog->setFixedSize(400, 300);

    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsDialog);

    // Заголовок
    QLabel *headerLabel = new QLabel("Текст приказа", detailsDialog);
    headerLabel->setAlignment(Qt::AlignCenter);
    QFont headerFont;
    headerFont.setBold(true);
    headerFont.setPointSize(12);
    headerLabel->setFont(headerFont);
    detailsLayout->addWidget(headerLabel);

    // Информация о приказе
    QString orderDetails = QString("%1 %2 на %3 в %4\nДиспетчер: %5\nИсполнитель:")
            .arg(order.value("operation_type").toInt() == 0 ? "Включить" : "Выключить")
            .arg(order.value("object").toString())
            .arg(order.value("control_point").toString())
            .arg(order.value("timestamp").toString())
            .arg(order.value("dispatcher").toString());

    QLabel *infoLabel = new QLabel(orderDetails, detailsDialog);
    detailsLayout->addWidget(infoLabel);

    // Выпадающий список исполнителей
    QComboBox *executorComboBox = new QComboBox(detailsDialog);
    if (order.value("control_type").toInt() == 0) {
        // Ручное управление
        QStringList personnelFIO = DBManager::getInstance().getPersonnelFIO();
        if (!personnelFIO.isEmpty()) {
            executorComboBox->addItems(personnelFIO);
        } else {
            executorComboBox->addItem("Нет доступных исполнителей");
            executorComboBox->setEnabled(false);
        }
    } else {
        // Автоматическое управление
        executorComboBox->addItem(order.value("dispatcher").toString());
        executorComboBox->setEnabled(false);
    }
    detailsLayout->addWidget(executorComboBox);

    // Кнопки
    QPushButton *executeButton = new QPushButton("Выполнить", detailsDialog);
    QPushButton *executeViaRUButton = new QPushButton("Выполнить через РУ", detailsDialog);
    QPushButton *cancelButton = new QPushButton("Отменить", detailsDialog);

    // Доступность кнопки "Выполнить"
    if (order.value("control_type").toInt() == 0) {
        executeButton->setEnabled(false); // Деактивируем для ручного управления
    }

    detailsLayout->addWidget(executeButton);
    detailsLayout->addWidget(executeViaRUButton);
    detailsLayout->addWidget(cancelButton);

    // Обработка кнопок
    connect(cancelButton, &QPushButton::clicked, detailsDialog, &QDialog::reject);

    connect(executeButton, &QPushButton::clicked, this, [=]() {
        detailsDialog->accept(); // Закрываем первый диалог
        openExecutionDialog(order, executorComboBox->currentText(), false); // Выполнение приказа
    });

    connect(executeViaRUButton, &QPushButton::clicked, this, [=]() {
        detailsDialog->accept(); // Закрываем первый диалог
        openExecutionDialog(order, executorComboBox->currentText(), true); // Выполнение через РУ
    });

    detailsDialog->exec();
    detailsDialog->deleteLater();
}


void MainWindow::openExecutionDialog(const QJsonObject &order, const QString &executor, bool viaRU) {
    QDialog *executionDialog = new QDialog(this);
    executionDialog->setWindowTitle(QString("Выполнение приказа №%1").arg(order.value("id").toInt()));
    executionDialog->setFixedSize(400, 300);

    QVBoxLayout *executionLayout = new QVBoxLayout(executionDialog);

    // Добавляем информацию о приказе
    QString orderDetails = QString("%1 %2 на %3 в %4\nДиспетчер: %5\nИсполнитель: %6")
            .arg(order.value("operation_type").toInt() == 0 ? "Включить" : "Выключить")
            .arg(order.value("object").toString())
            .arg(order.value("control_point").toString())
            .arg(order.value("timestamp").toString())
            .arg(order.value("dispatcher").toString())
            .arg(executor);

    QLabel *infoLabel = new QLabel(orderDetails, executionDialog);
    executionLayout->addWidget(infoLabel);

    QLabel *timerLabel = new QLabel("До выполнения приказа: 10 секунд", executionDialog);
    executionLayout->addWidget(timerLabel);

    QPushButton *cancelButton = new QPushButton("Отменить", executionDialog);
    executionLayout->addWidget(cancelButton);

    QTimer *countdownTimer = new QTimer(executionDialog);
    countdownTimer->setInterval(1000);
    int countdown = 10;

    connect(countdownTimer, &QTimer::timeout, this, [=]() mutable {
        countdown--;
        timerLabel->setText(QString("До выполнения приказа: %1 секунд").arg(countdown));
        if (countdown <= 0) {
            countdownTimer->stop();
            executionDialog->accept();
            openResponseDialog(order, executor, viaRU);
        }
    });

    connect(cancelButton, &QPushButton::clicked, executionDialog, [=]() {
        countdownTimer->stop();
        executionDialog->reject();
    });

    countdownTimer->start();
    executionDialog->exec();
    executionDialog->deleteLater();
}

void MainWindow::openResponseDialog(const QJsonObject &order, const QString &executor, bool viaRU) {
    QDialog *responseDialog = new QDialog(this);
    responseDialog->setWindowTitle("Ожидание ответа");
    responseDialog->setFixedSize(400, 300);

    QVBoxLayout *responseLayout = new QVBoxLayout(responseDialog);

    // Добавляем информацию о приказе
    QString orderDetails = QString("%1 %2 на %3 в %4\nДиспетчер: %5\nИсполнитель: %6")
            .arg(order.value("operation_type").toInt() == 0 ? "Включить" : "Выключить")
            .arg(order.value("object").toString())
            .arg(order.value("control_point").toString())
            .arg(order.value("timestamp").toString())
            .arg(order.value("dispatcher").toString())
            .arg(executor);

    QLabel *infoLabel = new QLabel(orderDetails, responseDialog);
    responseLayout->addWidget(infoLabel);

    QLabel *timerLabel = new QLabel("Ожидание ответа: 10 секунд", responseDialog);
    responseLayout->addWidget(timerLabel);

    // Отправляем команду на сервер
    QJsonObject commandObj;
    commandObj["command"] = viaRU ? "execute_order_ru" : "execute_order";
    commandObj["order_id"] = order.value("id").toInt();
    commandObj["executor"] = executor;

    emit sendCommannd(commandObj["command"].toString(),
                     QJsonDocument(commandObj).toJson(QJsonDocument::Compact));

    waitingForResponse = true;

    QTimer *responseTimer = new QTimer(responseDialog);
    responseTimer->setInterval(1000);
    int responseCountdown = 10;

    connect(responseTimer, &QTimer::timeout, this, [=]() mutable {
        responseCountdown--;
        timerLabel->setText(QString("Ожидание ответа: %1 секунд").arg(responseCountdown));
        if (responseCountdown <= 0) {
            responseTimer->stop();
            waitingForResponse = false;
            QMessageBox::warning(responseDialog, "Ошибка", "Приказ не выполнен: время ожидания истекло!");
            responseDialog->reject();
        }
    });

    connect(client, &arm_client::messageReceived, this, [=](const QString &message) {
        if (message.startsWith("OK:")) {
            responseTimer->stop();
            waitingForResponse = false;

            // Обновляем состояние в БД
            DBManager &dbManager = DBManager::getInstance();
            dbManager.updateLibraryState(1 - order.value("operation_type").toInt(),
                                       order.value("object_id").toInt());

            // Удаляем выполненный приказ
            removeOrderFromJson(order.value("id").toInt());

            // Обновляем интерфейс
            updateListWidgetFromJson();

            QMessageBox::information(responseDialog, "Успех", "Приказ успешно выполнен!");
            responseDialog->accept();

            widget->view->updateScene();
        }
    });

    responseTimer->start();
    responseDialog->exec();
    responseDialog->deleteLater();
}

// void MainWindow::onOrderWidgetClicked(const QJsonObject &order) {
//     int id = order.value("id").toInt();
//
//     // Создаем диалоговое окно
//     QDialog *dialog = new QDialog(this);
//     dialog->setWindowTitle(QString("Приказ №%1").arg(id));
//     dialog->setFixedSize(400, 300);
//
//     QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);
//
//     // Заголовок "Текст приказа"
//     QLabel *headerLabel = new QLabel("Текст приказа", dialog);
//     headerLabel->setAlignment(Qt::AlignCenter);
//     QFont headerFont;
//     headerFont.setBold(true);
//     headerFont.setPointSize(12);
//     headerLabel->setFont(headerFont);
//     dialogLayout->addWidget(headerLabel);
//
//     QString orderDetails = QString("%1 %2 на %3 в %4\nДиспетчер: %5\nИсполнитель:")
//             .arg(order.value("operation_type").toInt() == 0 ? "Включить" : "Выключить")
//             .arg(order.value("object").toString())
//             .arg(order.value("control_point").toString())
//             .arg(order.value("timestamp").toString())
//             .arg(order.value("dispatcher").toString());
//
//     QLabel *infoLabel = new QLabel(orderDetails, dialog);
//     dialogLayout->addWidget(infoLabel);
//
//     // Кнопки для выполнения приказа
//     QPushButton *executeButton = new QPushButton("Выполнить", dialog);
//     QPushButton *cancelButton = new QPushButton("Отменить", dialog);
//     dialogLayout->addWidget(executeButton);
//     dialogLayout->addWidget(cancelButton);
//
//     // Обработка кнопок
//     connect(executeButton, &QPushButton::clicked, this, [=]() {
//         // Логика выполнения приказа
//         dialog->accept();
//     });
//
//     connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);
//
//     dialog->exec();
//     dialog->deleteLater();
// }

// void MainWindow::setupConnections() {
//     connect(ui->listWidget, &QListWidget::itemClicked, this, &MainWindow::onItemClicked);
// }

// void MainWindow::ReadMessageReceivedtest(const QString &message) {
//     messageStatus = message;
// }

// void MainWindow::onItemClicked(QListWidgetItem *item) {
//     // Получить виджет элемента
//     QWidget *orderWidget = ui->listWidget->itemWidget(item);
//     QLabel *label = orderWidget ? orderWidget->findChild<QLabel *>() : nullptr;
//     QString orderInfo = label ? label->text() : "Нет данных";
//
//     // Извлечение id
//     int id = -1;
//     QRegularExpression idRegex("Приказ №(\\d+)");
//     QRegularExpressionMatch idMatch = idRegex.match(orderInfo);
//     if (idMatch.hasMatch()) {
//         id = idMatch.captured(1).toInt();
//     }
//
//     // Загрузка данных из JSON
//     QFile file("../orders_lib/orders.json");
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//         QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл JSON");
//         return;
//     }
//
//     QByteArray jsonData = file.readAll();
//     file.close();
//
//     QJsonDocument doc = QJsonDocument::fromJson(jsonData);
//     QJsonArray ordersArray = doc.array();
//
//     QJsonObject orderObject;
//     for (const auto &order: ordersArray) {
//         if (order.toObject()["id"].toInt() == id) {
//             orderObject = order.toObject();
//             break;
//         }
//     }
//
//     if (orderObject.isEmpty()) {
//         // Приказ не найден в JSON-файле, игнорируем клик
//         return;
//     }
//
//     // Создаем диалоговое окно
//     QDialog *dialog = new QDialog(this);
//     dialog->setWindowTitle(QString("Приказ №%1").arg(id));
//     dialog->setFixedSize(400, 300);
//
//     // Создаем лейаут для диалогового окна
//     QVBoxLayout *dialogLayout = new QVBoxLayout(dialog);
//
//     // Заголовок "Текст приказа" по центру
//     QLabel *headerLabel = new QLabel("Текст приказа", dialog);
//     headerLabel->setAlignment(Qt::AlignCenter);
//     QFont headerFont;
//     headerFont.setBold(true);
//     headerFont.setPointSize(12);
//     headerLabel->setFont(headerFont);
//     dialogLayout->addWidget(headerLabel);
//
//     // Отображаем информацию о приказе
//     QString orderDetails = QString("%1 %2 на %3 в %4\nДиспетчер: %5\nИсполнитель:")
//             .arg(orderObject["operation_type"].toInt() == 0 ? "Включить" : "Выключить")
//             .arg(orderObject["object"].toString())
//             .arg(orderObject["control_point"].toString().trimmed())
//             .arg(orderObject["timestamp"].toString())
//             .arg(orderObject["dispatcher"].toString());
//
//     QLabel *infoLabel = new QLabel(orderDetails, dialog);
//     dialogLayout->addWidget(infoLabel);
//
//     // Выпадающий список для выбора исполнителя
//     QComboBox *executorComboBox = new QComboBox(dialog);
//     if (orderObject["control_type"].toInt() == 0) {
//         // Ручное управление
//         QStringList personnelFIO = DBManager::getInstance().getPersonnelFIO();
//         if (!personnelFIO.isEmpty()) {
//             executorComboBox->addItems(personnelFIO);
//         } else {
//             executorComboBox->addItem("Нет доступных исполнителей");
//             executorComboBox->setEnabled(false);
//         }
//     } else {
//         // Автоматическое управление
//         executorComboBox->addItem(orderObject["dispatcher"].toString());
//         executorComboBox->setEnabled(false);
//     }
//     dialogLayout->addWidget(executorComboBox);
//
//     // Таймер для отображения времени ожидания
//     QLabel *timerLabel = new QLabel(dialog);
//     dialogLayout->addWidget(timerLabel);
//
//     // Кнопки
//     QPushButton *executeButton = new QPushButton("Выполнить", dialog);
//     QPushButton *executeViaRUButton = new QPushButton("Выполнить через РУ", dialog);
//     QPushButton *cancelButton = new QPushButton("Отменить", dialog);
//
//     if (orderObject["control_type"].toInt() == 0) {
//         executeButton->setEnabled(false);
//     }
//
//     dialogLayout->addWidget(executeButton);
//     dialogLayout->addWidget(executeViaRUButton);
//     dialogLayout->addWidget(cancelButton);
//
//     // Кнопка отмены выполнения (изначально скрыта)
//     QPushButton *cancelExecutionButton = new QPushButton("Отмена выполнения", dialog);
//     cancelExecutionButton->setVisible(false);
//     dialogLayout->addWidget(cancelExecutionButton);
//
//     // Локальная переменная для отслеживания отмены
//     bool executionCancelled = false;
//
//     // Функция для начала выполнения приказа
//     auto startOrderExecution = [=](const QString &command) {
//         if (executionCancelled) {
//             return;
//         }
//
//         waitingForResponse = true;
//
//         QJsonObject commandObj;
//         commandObj["command"] = command;
//         commandObj["order_id"] = id;
//         commandObj["executor"] = executorComboBox->currentText();
//
//         emit sendCommannd(command, QJsonDocument(commandObj).toJson(QJsonDocument::Compact));
//
//         // Таймер обратного отсчета ожидания ответа
//         int remainingTime = 10;
//         timerLabel->setText(QString("Ожидание ответа: %1 секунд").arg(remainingTime));
//
//         QTimer *countdownTimer = new QTimer(this);
//         countdownTimer->setInterval(1000);
//         connect(countdownTimer, &QTimer::timeout, this, [=]() mutable {
//             remainingTime--;
//             timerLabel->setText(QString("Ожидание ответа: %1 секунд").arg(remainingTime));
//             if (remainingTime <= 0) {
//                 countdownTimer->stop();
//                 countdownTimer->deleteLater();
//             }
//         });
//         countdownTimer->start();
//
//         // Обработка получения ответа от сервера
//         connect(client, &arm_client::messageReceived, this, [=](const QString &message) {
//             if (executionCancelled || !message.startsWith("OK:")) {
//                 return;
//             }
//
//             waitingForResponse = false;
//             countdownTimer->stop();
//             countdownTimer->deleteLater();
//
//             // Преобразование QJsonObject в nlohmann::json
//             nlohmann::json orderJson = nlohmann::json::parse(QJsonDocument(orderObject).toJson().toStdString());
//
//             // Удаление приказа из JSON
//             removeOrderFromJson(orderJson);
//
//             DBManager &dbManager = DBManager::getInstance();
//             bool success = dbManager.updateLibraryState(1 - orderObject["operation_type"].toInt(),
//                                                         orderObject["object_id"].toInt());
//
//             widget->updateScene();
//
//             // Отображение уведомления с помощью QMessageBox
//             QMessageBox::information(dialog, "Успех", "Приказ успешно выполнен!");
//
//             // Обновление списка приказов
//             updateListWidgetFromJson();
//
//             // Закрытие основного диалогового окна приказа
//             dialog->accept();
//         });
//
//         // Обработка окончания времени ожидания ответа
//         QTimer::singleShot(10000, this, [=]() {
//             if (waitingForResponse) {
//                 QMessageBox::warning(dialog, "Ошибка", "Приказ не выполнен: время ожидания истекло!");
//                 dialog->reject();
//             }
//         });
//     };
//
//     // Функция обработки выполнения приказа
//     auto executeOrder = [&](const QString &command) {
//         executionCancelled = false; // Сбрасываем флаг отмены
//         executeButton->setEnabled(false);
//         executeViaRUButton->setEnabled(false);
//         cancelButton->setVisible(false);
//         cancelExecutionButton->setVisible(true);
//         timerLabel->setVisible(true);
//
//         int countdownTime = 10;
//         timerLabel->setText(QString("До выполнения приказа: %1 секунд").arg(countdownTime));
//
//         QTimer *countdownTimer = new QTimer(this);
//         countdownTimer->setInterval(1000);
//         connect(countdownTimer, &QTimer::timeout, this, [=]() mutable {
//             countdownTime--;
//             timerLabel->setText(QString("До выполнения приказа: %1 секунд").arg(countdownTime));
//             if (countdownTime <= 0) {
//                 countdownTimer->stop();
//                 countdownTimer->deleteLater();
//                 cancelExecutionButton->setEnabled(false);
//                 startOrderExecution(command);
//             }
//         });
//         countdownTimer->start();
//
//         // Обработка отмены выполнения
//         connect(cancelExecutionButton, &QPushButton::clicked, this, [&]() {
//             executionCancelled = true;
//             countdownTimer->stop();
//             countdownTimer->deleteLater();
//             timerLabel->setText("");
//             timerLabel->setVisible(true);
//             QMessageBox::information(dialog, "Отмена", "Выполнение приказа отменено.");
//             cancelExecutionButton->setVisible(false);
//             cancelButton->setVisible(true);
//             executeButton->setEnabled(true);
//             executeViaRUButton->setEnabled(true);
//         });
//     };
//
//     // Обработка кнопок
//     connect(executeButton, &QPushButton::clicked, this, [=]() {
//         executeOrder("execute_order");
//     });
//
//     connect(executeViaRUButton, &QPushButton::clicked, this, [=]() {
//         executeOrder("execute_order_ru");
//     });
//
//     connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);
//
//     dialog->exec();
//     dialog->deleteLater();
// }


quint16 MainWindow::readMaxOrderId(const QString &jsonFilePath) {
    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Не удалось открыть файл:" << jsonFilePath;
        return 0;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (!doc.isArray()) {
        qWarning() << "Некорректный формат JSON: ожидается массив.";
        return 0;
    }

    QJsonArray jsonArray = doc.array();
    qint16 maxId = 0;

    for (const QJsonValue &value: jsonArray) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            if (obj.contains("id")) {
                int id = obj["id"].toInt();
                if (id > maxId) {
                    maxId = id;
                }
            }
        }
    }

    return maxId;

}

