#include "MainView.h"

#include <fstream>
#include <iostream>
#include <QScrollBar>
#include <QDialog>
#include <QMessageBox>
#include "db_lib/DBManager.h"
#include <sstream>
#include <iomanip>
#include <QTableWidget>
#include "socket_client/lib/arm_client.h"
#include <nlohmann/json.hpp>

#include "MainWindow.h"
#include "../orders_lib/Order.h"


QString MainView::getUserLogin(const QString &filePath) {
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

MainView::MainView(QGraphicsScene *parent, MainWindow *_main_window) : QGraphicsView(parent){
    main_window = _main_window;
    // Подключаем слот, который будет отслеживать положение скроллбара
    scene = parent;
}

// MainView::MainView(QGraphicsScene *parent, MainWindow *_main_window) : QGraphicsView(parent), clientThread(new QThread),
//                                                                        clientWorker(new arm_client) {
//     main_window = _main_window;
//     // Подключаем слот, который будет отслеживать положение скроллбара
//     scene = parent;
//
//     clientWorker->moveToThread(clientThread);
//
//     // Связываем сигналы/слоты
//     connect(clientWorker, &arm_client::messageReceived, this, &MainView::onMessageReceived);
//     connect(clientWorker, &arm_client::messageReceived, this, &MainView::ReadMessageReceivedtest);
//     connect(clientWorker, &arm_client::errorOccurred, this, &MainView::onErrorOccurred);
//     connect(this, &MainView::sendCommannd, clientWorker, &arm_client::sendCommand);
//
//     // Запускаем поток
//     clientThread->start();
//
//     // Стартуем клиента
//     startClient("127.0.0.1", 3011);
// }

// void MainView::startClient(const QString &host, quint16 port) {
//     // Соединяемся с сервером через сигнал/слот
//     QMetaObject::invokeMethod(clientWorker, [=]() {
//         clientWorker->connectToServer(host, port);
//     });
// }

// void MainView::sendMessageToServer(const QString &action, const QString &object) {
//     emit sendCommannd(action, object); // Отправляем сигнал клиенту
// }
//
// void MainView::onErrorOccurred(const QString &error) {
//     qDebug() << "Error:" << error;
// }
//
// void MainView::showOrderDialog(QPoint &point) {
//     ;
// }

void DeleteLayout(QLayout *layout) {
    QLayoutItem *child;
    while ((child = layout->takeAt(0)) != nullptr) {
        QWidget *widget = child->widget();
        if (widget) {
            layout->removeWidget(widget); // Хотя takeAt уже удаляет из layout, на всякий случай
            delete widget; // Удаляем виджет (если нужно)
        }
        delete child; // Удаляем QLayoutItem
    }

    delete layout;
}

void MainView::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPoint point(event->pos().x(), event->pos().y());

        for (auto object: scheme_params.objects_vector) {
            std::string tp_obj = object->get_type_object();
            if (tp_obj == "Библиотечный объект") {
                QPoint original_point = point;

                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));

                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) &&
                    newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) &&
                    newPoint.y() <= object->get_height() / 2) {
                    transform.reset();

                    int hor_off = 30;
                    int ver_off = -30;

                    QDialog dialog(this);
                    dialog.setWindowTitle("Приказ");

                    dialog.move(event->globalX() + hor_off, event->globalY() + ver_off);

                    // Используем DBManager для получения данных об объекте
                    DBManager &dbManager = DBManager::getInstance();

                    QSqlQuery objectQuery = dbManager.getLibraryObjects();
                    QSqlQuery controlPointQuery = dbManager.getCPObjects();

                    QString id = "None";
                    QString name = "None";
                    QString cp_id = "None";
                    QString normal_state = "None";
                    QString fail_state = "None";
                    QString cur_state = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";
                    int control_type = 0;

                    this->cur_obj_id = object->get_id();

                    // Поиск данных об объекте
                    while (objectQuery.next()) {
                        if (objectQuery.value(0).toInt() == object->get_id()) {
                            id = objectQuery.value(0).toString();
                            name = objectQuery.value(1).toString();
                            cp_id = objectQuery.value(2).toString();
                            normal_state = objectQuery.value(3).toString();
                            fail_state = objectQuery.value(4).toString();
                            cur_state = objectQuery.value(5).toString();
                            obj_type = objectQuery.value(6).toString();
                            obj_name = objectQuery.value(7).toString();
                            control_type = objectQuery.value(8).toInt();

                            // Поиск данных о контрольной точке
                            controlPointQuery.first();
                            do {
                                if (controlPointQuery.value(0).toString() == cp_id) {
                                    if (controlPointQuery.value(1).toString() == "None") {
                                        cp_name = controlPointQuery.value(1).toString();
                                    } else {
                                        cp_name = controlPointQuery.value(2).toString() + " " + controlPointQuery.value(
                                                      1).toString();
                                    }
                                    break;
                                }
                            } while (controlPointQuery.next());
                        }
                    }

                    // Создание интерфейса
                    QVBoxLayout *layout = new QVBoxLayout();

                    QPushButton *createOrderOffButton = new QPushButton("Отключить");
                    layout->addWidget(createOrderOffButton);

                    QPushButton *createOrderOnButton = new QPushButton("Включить");
                    layout->addWidget(createOrderOnButton);

                    dialog.setLayout(layout);
                    dialog.adjustSize();

                    QVBoxLayout *create_order_layout = new QVBoxLayout(&dialog);

                    QLabel *label = new QLabel(QString("Наим. контрольного пункта: %1").arg(cp_name));
                    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    create_order_layout->addWidget(label);

                    label = new QLabel(QString("Объект: %1").arg(name));
                    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    create_order_layout->addWidget(label);

                    label = new QLabel(QString("Диспетчер: %1").arg(getUserLogin("../user.cfg")));
                    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    create_order_layout->addWidget(label);

                    QString controlTypeText = control_type == 0 ? "Ручное управление" : "Автоматическое управление";
                    label = new QLabel(QString("Тип управления: %1").arg(controlTypeText));
                    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    create_order_layout->addWidget(label);

                    label = new QLabel();
                    create_order_layout->addWidget(label);

                    QPushButton *createOrderButton = new QPushButton("Создать приказ");
                    create_order_layout->addWidget(createOrderButton);

                    actionType action;

                    connect(createOrderOnButton, &QPushButton::clicked, [&]() {
                        DeleteLayout(layout);

                        label->setText("Тип операции: Включить");
                        label->setStyleSheet("color: red;");
                        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);

                        action = switchOn;

                        dialog.setLayout(create_order_layout);
                        dialog.adjustSize();
                    });

                    connect(createOrderOffButton, &QPushButton::clicked, [&]() {
                        DeleteLayout(layout);

                        label->setText("Тип операции: Отключить");
                        label->setStyleSheet("color: green;");
                        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);

                        action = switchOff;

                        dialog.setLayout(create_order_layout);
                        dialog.adjustSize();
                    });

                    connect(createOrderButton, &QPushButton::clicked, [&]() {
                        createOrderButton->setEnabled(false);

                        // if (control_type) {
                        //     main_window->Orders.add({});
                        // }
                        // else {
                        //     main_window->Orders.add({});
                        // }

                        // Сохранение данных приказа в JSON
                        nlohmann::json orderObject;
                        orderObject["object_id"] = id.toInt();
                        orderObject["id"] = ++main_window->max_order_id;
                        orderObject["control_point"] = cp_name.toStdString();
                        orderObject["object"] = name.toStdString();
                        orderObject["operation_type"] = action;
                        orderObject["dispatcher"] = getUserLogin("../user.cfg").toStdString();
                        orderObject["control_type"] = control_type;

                        auto now = std::chrono::system_clock::now();
                        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                        std::tm now_tm;
                        localtime_r(&now_c, &now_tm);
                        char timestamp_str[26];
                        std::strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S", &now_tm);
                        orderObject["timestamp"] = timestamp_str;

                        // Чтение текущего JSON
                        std::ifstream ordersFileRead("../orders_lib/orders.json");
                        nlohmann::json ordersData;
                        if (ordersFileRead.is_open()) {
                            try {
                                ordersFileRead >> ordersData;
                            } catch (const nlohmann::json::parse_error &e) {
                                std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
                                ordersFileRead.close();
                                return;
                            }
                            ordersFileRead.close();
                        } else {
                            ordersData = nlohmann::json::array();
                        }

                        // Добавление нового приказа
                        ordersData.push_back(orderObject);

                        // Запись в файл
                        std::ofstream ordersFileWrite("../orders_lib/orders.json");
                        if (ordersFileWrite.is_open()) {
                            ordersFileWrite << std::setw(4) << ordersData << std::endl;
                            ordersFileWrite.close();
                            createOrderButton->setText("Приказ создан");
                        } else {
                            std::cerr << "Не удалось открыть файл orders.json для записи." << std::endl;
                            createOrderButton->setText("Ошибка записи файла");
                        }

                        main_window->updateListWidgetFromJson();
                    });

                    dialog.exec();
                }
            }
        }
    }
}

// void MainView::ReadMessageReceivedtest(const QString &message) {
//     messageStatus = message;
// }


void MainView::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        QPoint point(event->pos().x(), event->pos().y());

        for (auto object: scheme_params.objects_vector) {
            std::string tp_obj = object->get_type_object();
            if (tp_obj == "Библиотечный объект") {
                QPoint original_point = point;

                // Создаем объект преобразования
                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2) {
                    transform.reset();

                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();
                    newWindow->setFixedWidth(270);

                    newWindow->move(event->globalX() + hor_off, event->globalY() + ver_off);

                    // Получаем данные из DBManager
                    DBManager &dbManager = DBManager::getInstance();

                    QString id = "None";
                    QString name = "None";
                    QString cp_id = "None";
                    QString normal_state = "None";
                    QString fail_state = "None";
                    QString cur_state = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";
                    int control_type = 0;

                    this->cur_obj_id = object->get_id();

                    // Получаем информацию об объекте
                    QSqlQuery libraryObjectsQuery = dbManager.getLibraryObjects();
                    while (libraryObjectsQuery.next()) {
                        if (libraryObjectsQuery.value(0).toInt() == object->get_id()) {
                            id = libraryObjectsQuery.value(0).toString();
                            name = libraryObjectsQuery.value(1).toString();
                            cp_id = libraryObjectsQuery.value(2).toString();
                            normal_state = libraryObjectsQuery.value(3).toString();
                            fail_state = libraryObjectsQuery.value(4).toString();
                            cur_state = libraryObjectsQuery.value(5).toString();
                            obj_type = libraryObjectsQuery.value(6).toString();
                            obj_name = libraryObjectsQuery.value(7).toString();
                            control_type = libraryObjectsQuery.value(8).toInt();
                            break; // Достаточно одного совпадения
                        }
                    }

                    // Получаем имя контрольного пункта
                    QSqlQuery controlPointsQuery = dbManager.getCPObjects();
                    while (controlPointsQuery.next()) {
                        if (controlPointsQuery.value(0).toString() == cp_id) {
                            if (controlPointsQuery.value(1).toString() == "None") {
                                cp_name = controlPointsQuery.value(1).toString();
                            } else {
                                cp_name = controlPointsQuery.value(2).toString() + " " + controlPointsQuery.value(1).
                                          toString();
                            }
                            break; // Достаточно одного совпадения
                        }
                    }

                    // Получаем список объектов для таблицы
                    QSqlQuery cpObjectsQuery = dbManager.getObjectsByCPId(cp_id.toInt());

                    // Создаем интерфейс
                    QVBoxLayout *mainLayout = new QVBoxLayout(newWindow);

                    auto addRow = [](QVBoxLayout *layout, const QString &labelText, const QString &valueText) {
                        QHBoxLayout *rowLayout = new QHBoxLayout();
                        QLabel *label = new QLabel(labelText);
                        QLabel *value = new QLabel(valueText);
                        value->setStyleSheet("QLabel { color : blue; }");
                        rowLayout->addWidget(label);
                        rowLayout->addWidget(value);
                        layout->addLayout(rowLayout);
                    };

                    // Добавляем строки с данными
                    addRow(mainLayout, "Наименование:", name);
                    addRow(mainLayout, "Идентификатор:", id);
                    addRow(mainLayout, "Текущее значение:", cur_state);
                    addRow(mainLayout, "Нормальное положение:", normal_state);
                    addRow(mainLayout, "Значение при ошибке:", fail_state);
                    addRow(mainLayout, "Наим. контр. пункта:", cp_name);
                    addRow(mainLayout, "Диспетчерское наименование:", obj_name);
                    addRow(mainLayout, "Тип объекта:", obj_type);

                    // Добавляем строку с типом управления
                    QString controlTypeText = control_type == 0 ? "Ручное управление" : "Автоматическое управление";
                    addRow(mainLayout, "Тип управления:", controlTypeText);

                    // Создаем таблицу для объектов контрольного пункта
                    QTableWidget *table = new QTableWidget();
                    table->setColumnCount(2);
                    table->setHorizontalHeaderItem(0, new QTableWidgetItem("id объекта"));
                    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя объекта"));

                    // Заполняем таблицу данными
                    int row = 0;
                    while (cpObjectsQuery.next()) {
                        table->insertRow(row);
                        for (int col = 0; col < 2; ++col) {
                            QTableWidgetItem *item = new QTableWidgetItem(cpObjectsQuery.value(col).toString());
                            table->setItem(row, col, item);
                        }
                        ++row;
                    }

                    // Настраиваем высоту таблицы
                    if (table->rowCount() >= 7) {
                        table->setFixedHeight(250);
                    }
                    table->setFixedWidth(256);
                    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

                    // Добавляем таблицу в интерфейс
                    QHBoxLayout *row9Layout = new QHBoxLayout();
                    QLabel *label9 = new QLabel("Объекты этого контр. пункта:");
                    row9Layout->addWidget(label9);
                    mainLayout->addLayout(row9Layout);

                    QHBoxLayout *row10Layout = new QHBoxLayout();
                    row10Layout->addWidget(table);
                    mainLayout->addLayout(row10Layout);

                    // Показываем меню
                    newWindow->show();
                }
            } else if (tp_obj == "Телеизмерение") {
                QPoint original_point = point;

                // Создаем объект преобразования
                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2) {
                    transform.reset();

                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();
                    newWindow->setFixedWidth(270);

                    newWindow->move(event->globalX() + hor_off, event->globalY() + ver_off);

                    // Используем DBManager для извлечения данных
                    DBManager &dbManager = DBManager::getInstance();

                    QString id = "None";
                    QString name = "None";
                    QString cp_id = "None";
                    QString cur_value = "None";
                    QString min_value = "None";
                    QString max_value = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";
                    QString n_l_l = "None"; // Нижняя нормальная граница
                    QString n_u_l = "None"; // Верхняя нормальная граница
                    QString c_l_l = "None"; // Нижняя критическая граница
                    QString c_u_l = "None"; // Верхняя критическая граница

                    this->cur_obj_id = object->get_id();

                    // Получаем данные о телеизмерении
                    QSqlQuery measurementObjectsQuery = dbManager.getMeasurementObjects();
                    while (measurementObjectsQuery.next()) {
                        if (measurementObjectsQuery.value(0).toInt() == object->get_id()) {
                            id = measurementObjectsQuery.value(0).toString();
                            name = measurementObjectsQuery.value(1).toString();
                            cp_id = measurementObjectsQuery.value(2).toString();
                            cur_value = QString::number(measurementObjectsQuery.value(3).toDouble(), 'f', 2);
                            min_value = QString::number(measurementObjectsQuery.value(4).toDouble(), 'f', 2);
                            max_value = QString::number(measurementObjectsQuery.value(5).toDouble(), 'f', 2);
                            obj_type = measurementObjectsQuery.value(6).toString();
                            obj_name = measurementObjectsQuery.value(7).toString();
                            n_l_l = QString::number(measurementObjectsQuery.value(8).toDouble(), 'f', 2);
                            n_u_l = QString::number(measurementObjectsQuery.value(9).toDouble(), 'f', 2);
                            c_l_l = QString::number(measurementObjectsQuery.value(10).toDouble(), 'f', 2);
                            c_u_l = QString::number(measurementObjectsQuery.value(11).toDouble(), 'f', 2);
                            break; // Достаточно одного совпадения
                        }
                    }

                    // Получаем имя контрольного пункта
                    QSqlQuery controlPointsQuery = dbManager.getCPObjects();
                    while (controlPointsQuery.next()) {
                        if (controlPointsQuery.value(0).toString() == cp_id) {
                            cp_name = controlPointsQuery.value(1).toString();
                            break; // Достаточно одного совпадения
                        }
                    }

                    // Список объектов контрольного пункта
                    QSqlQuery cpObjectsQuery = dbManager.getObjectsByCPId(cp_id.toInt());

                    // Создаем интерфейс
                    QVBoxLayout *mainLayout = new QVBoxLayout(newWindow);

                    auto addRow = [](QVBoxLayout *layout, const QString &labelText, const QString &valueText) {
                        QHBoxLayout *rowLayout = new QHBoxLayout();
                        QLabel *label = new QLabel(labelText);
                        QLabel *value = new QLabel(valueText);
                        value->setStyleSheet("QLabel { color : blue; }");
                        rowLayout->addWidget(label);
                        rowLayout->addWidget(value);
                        layout->addLayout(rowLayout);
                    };

                    // Добавляем строки с данными
                    addRow(mainLayout, "Наименование:", name);
                    addRow(mainLayout, "Идентификатор:", id);
                    addRow(mainLayout, "Текущее значение:", cur_value);
                    addRow(mainLayout, "Минимальное значение:", min_value);
                    addRow(mainLayout, "Максимальное значение:", max_value);
                    addRow(mainLayout, "Наим. контр. пункта:", cp_name);
                    addRow(mainLayout, "Диспетчерское наименование:", obj_name);
                    addRow(mainLayout, "Тип объекта:", obj_type);
                    addRow(mainLayout, "Макс. нормальное отклонение:", n_u_l);
                    addRow(mainLayout, "Мин. нормальное отклонение:", n_l_l);
                    addRow(mainLayout, "Макс. предельное отклонение:", c_u_l);
                    addRow(mainLayout, "Мин. предельное отклонение:", c_l_l);

                    // Создаем таблицу для объектов контрольного пункта
                    QTableWidget *table = new QTableWidget();
                    table->setColumnCount(2);
                    table->setHorizontalHeaderItem(0, new QTableWidgetItem("id объекта"));
                    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя объекта"));

                    // Заполняем таблицу данными
                    int row = 0;
                    while (cpObjectsQuery.next()) {
                        table->insertRow(row);
                        for (int col = 0; col < 2; ++col) {
                            QTableWidgetItem *item = new QTableWidgetItem(cpObjectsQuery.value(col).toString());
                            table->setItem(row, col, item);
                        }
                        ++row;
                    }

                    // Настраиваем высоту таблицы
                    if (table->rowCount() >= 7) {
                        table->setFixedHeight(250);
                    }
                    table->setFixedWidth(256);
                    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

                    // Добавляем таблицу в интерфейс
                    QHBoxLayout *row13Layout = new QHBoxLayout();
                    QLabel *label13 = new QLabel("Объекты этого контр. пункта:");
                    row13Layout->addWidget(label13);
                    mainLayout->addLayout(row13Layout);

                    QHBoxLayout *row14Layout = new QHBoxLayout();
                    row14Layout->addWidget(table);
                    mainLayout->addLayout(row14Layout);

                    // Показываем меню
                    newWindow->show();
                }
            } else if (tp_obj == "Телеконтроль") {
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2) {
                    transform.reset();

                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();
                    newWindow->setFixedWidth(260);

                    newWindow->move(event->globalX() + hor_off, event->globalY() + ver_off);

                    DBManager &dbManager = DBManager::getInstance();
                    QSqlQuery db_request_result = dbManager.getControlObjects();
                    QSqlQuery db_request_result_cp = dbManager.getCPObjects();

                    QString name = "None";
                    QString cp_id = "None";
                    QString id = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";
                    QSqlQuery cp_objects;

                    this->cur_obj_id = object->get_id();
                    while (db_request_result.next()) {
                        if (db_request_result.value(0).toInt() == object->get_id()) {
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            id = db_request_result.value(0).toString();
                            obj_type = db_request_result.value(6).toString();
                            obj_name = db_request_result.value(7).toString();

                            cp_objects = dbManager.getObjectsByCPId(cp_id.toInt());

                            while (db_request_result_cp.next()) {
                                if (db_request_result_cp.value(0).toString() == cp_id) {
                                    if (db_request_result_cp.value(1).toString() == "None") {
                                        cp_name = db_request_result_cp.value(1).toString();
                                    } else {
                                        cp_name = db_request_result_cp.value(2).toString() + " " +
                                                  db_request_result_cp.
                                                  value(1).toString();
                                    }
                                }
                            }
                        }
                    }

                    QVBoxLayout *mainLayout = new QVBoxLayout(newWindow);

                    QHBoxLayout *row1Layout = new QHBoxLayout();
                    QLabel *label1 = new QLabel("Наименование:");
                    QLabel *label1_1 = new QLabel(name);
                    label1_1->setStyleSheet("QLabel { color : blue; }");
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(label1_1);

                    QHBoxLayout *row2Layout = new QHBoxLayout();
                    QLabel *label2 = new QLabel("Идентификатор:");
                    QLabel *label2_2 = new QLabel(id);
                    label2_2->setStyleSheet("QLabel { color : blue; }");
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(label2_2);

                    QHBoxLayout *row6Layout = new QHBoxLayout();
                    QLabel *label6 = new QLabel("Наим. контр. пункта:");
                    QLabel *label6_6 = new QLabel(cp_name);
                    label6_6->setStyleSheet("QLabel { color : blue; }");
                    row6Layout->addWidget(label6);
                    row6Layout->addWidget(label6_6);

                    QHBoxLayout *row7Layout = new QHBoxLayout();
                    QLabel *label7 = new QLabel("Диспетчерское наименование:");
                    QLabel *label7_7 = new QLabel(obj_name);
                    label7_7->setStyleSheet("QLabel { color : blue; }");
                    row7Layout->addWidget(label7);
                    row7Layout->addWidget(label7_7);

                    QHBoxLayout *row8Layout = new QHBoxLayout();
                    QLabel *label8 = new QLabel("Тип объекта:");
                    QLabel *label8_8 = new QLabel(obj_type);
                    label8_8->setStyleSheet("QLabel { color : blue; }");
                    row8Layout->addWidget(label8);
                    row8Layout->addWidget(label8_8);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addLayout(row6Layout);
                    mainLayout->addLayout(row7Layout);
                    mainLayout->addLayout(row8Layout);

                    QTableWidget *table = new QTableWidget();

                    table->setColumnCount(2);
                    table->setHorizontalHeaderItem(0, new QTableWidgetItem("id объекта"));
                    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя объекта"));

                    // Заполняем таблицу данными
                    int row = 0;
                    while (cp_objects.next()) {
                        table->insertRow(row);
                        for (int col = 0; col < 2; ++col) {
                            QTableWidgetItem *item = new QTableWidgetItem(cp_objects.value(col).toString());
                            table->setItem(row, col, item);
                        }
                        ++row;
                    }
                    if (table->rowCount() >= 7) {
                        table->setFixedHeight(250);
                    }
                    table->setFixedWidth(256);
                    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

                    QHBoxLayout *row13Layout = new QHBoxLayout();
                    QLabel *label13 = new QLabel("Объекты этого контр. пункта:");
                    row13Layout->addWidget(label13);
                    mainLayout->addLayout(row13Layout);

                    QHBoxLayout *row14Layout = new QHBoxLayout();
                    row14Layout->addWidget(table);
                    mainLayout->addLayout(row14Layout);

                    newWindow->show();
                }
            } else if (tp_obj == "Телесигнализация") {
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2) {
                    transform.reset();

                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();
                    newWindow->setFixedWidth(260);

                    newWindow->move(event->globalX() + hor_off, event->globalY() + ver_off);

                    DBManager &dbManager = DBManager::getInstance();
                    QSqlQuery db_request_result = dbManager.getSignalObjects();
                    QSqlQuery db_request_result_cp = dbManager.getCPObjects();

                    QString name = "None";
                    QString cp_id = "None";
                    QString id = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";
                    QSqlQuery cp_objects;

                    this->cur_obj_id = object->get_id();
                    while (db_request_result.next()) {
                        if (db_request_result.value(0).toInt() == object->get_id()) {
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            id = db_request_result.value(0).toString();
                            obj_type = db_request_result.value(3).toString();
                            obj_name = db_request_result.value(4).toString();
                            cp_objects = dbManager.getObjectsByCPId(cp_id.toInt());

                            while (db_request_result_cp.next()) {
                                if (db_request_result_cp.value(0).toString() == cp_id) {
                                    if (db_request_result_cp.value(1).toString() == "None") {
                                        cp_name = db_request_result_cp.value(1).toString();
                                    } else {
                                        cp_name = db_request_result_cp.value(2).toString() + " " +
                                                  db_request_result_cp.
                                                  value(1).toString();
                                    }
                                }
                            }
                        }
                    }

                    QVBoxLayout *mainLayout = new QVBoxLayout(newWindow);

                    QHBoxLayout *row1Layout = new QHBoxLayout();
                    QLabel *label1 = new QLabel("Наименование:");
                    QLabel *label1_1 = new QLabel(name);
                    label1_1->setStyleSheet("QLabel { color : blue; }");
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(label1_1);

                    QHBoxLayout *row2Layout = new QHBoxLayout();
                    QLabel *label2 = new QLabel("Идентификатор:");
                    QLabel *label2_2 = new QLabel(id);
                    label2_2->setStyleSheet("QLabel { color : blue; }");
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(label2_2);

                    QHBoxLayout *row6Layout = new QHBoxLayout();
                    QLabel *label6 = new QLabel("Наим. контр. пункта:");
                    QLabel *label6_6 = new QLabel(cp_name);
                    label6_6->setStyleSheet("QLabel { color : blue; }");
                    row6Layout->addWidget(label6);
                    row6Layout->addWidget(label6_6);

                    QHBoxLayout *row7Layout = new QHBoxLayout();
                    QLabel *label7 = new QLabel("Диспетчерское наименование:");
                    QLabel *label7_7 = new QLabel(obj_name);
                    label7_7->setStyleSheet("QLabel { color : blue; }");
                    row7Layout->addWidget(label7);
                    row7Layout->addWidget(label7_7);

                    QHBoxLayout *row8Layout = new QHBoxLayout();
                    QLabel *label8 = new QLabel("Тип объекта:");
                    QLabel *label8_8 = new QLabel(obj_type);
                    label8_8->setStyleSheet("QLabel { color : blue; }");
                    row8Layout->addWidget(label8);
                    row8Layout->addWidget(label8_8);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addLayout(row6Layout);
                    mainLayout->addLayout(row7Layout);
                    mainLayout->addLayout(row8Layout);

                    QTableWidget *table = new QTableWidget();

                    table->setColumnCount(2);
                    table->setHorizontalHeaderItem(0, new QTableWidgetItem("id объекта"));
                    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя объекта"));

                    // Заполняем таблицу данными
                    int row = 0;
                    while (cp_objects.next()) {
                        table->insertRow(row);
                        for (int col = 0; col < 2; ++col) {
                            QTableWidgetItem *item = new QTableWidgetItem(cp_objects.value(col).toString());
                            table->setItem(row, col, item);
                        }
                        ++row;
                    }
                    if (table->rowCount() >= 7) {
                        table->setFixedHeight(250);
                    }
                    table->setFixedWidth(256);
                    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

                    QHBoxLayout *row13Layout = new QHBoxLayout();
                    QLabel *label13 = new QLabel("Объекты этого контр. пункта:");
                    row13Layout->addWidget(label13);
                    mainLayout->addLayout(row13Layout);

                    QHBoxLayout *row14Layout = new QHBoxLayout();
                    row14Layout->addWidget(table);
                    mainLayout->addLayout(row14Layout);

                    newWindow->show();
                }
            }
        }
    }
}


void MainView::updateScene() {
    DBManager &dbManager = DBManager::getInstance();
    QSqlQuery db_request_result = dbManager.getObjects();
    QSqlQuery db_request_result_cp = dbManager.getCPObjects();
    std::string help_text;

    for (auto object: scheme_params.objects_vector) {
        if (object->get_type_object() == "Библиотечный объект") {
            while (db_request_result.next()) {
                if (db_request_result.value(0).toInt() == object->get_id()) {
                    object->set_condition(db_request_result.value(2).toInt());
                    while (db_request_result_cp.next()) {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt()) {
                            help_text = db_request_result.value(1).toString().toStdString() + " (" +
                                        db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                            break;
                        }
                    }
                    break;
                }
            }
            db_request_result.seek(0);
            db_request_result_cp.seek(0);
        } else if (object->get_type_object() == "Телеизмерение") {
            QSqlQuery measurementQuery = dbManager.getMeasurementObjects();
            while (measurementQuery.next()) {
                if (measurementQuery.value(0).toInt() == object->get_id()) {
                    object->set_text(measurementQuery.value(3).toString().toStdString());
                    while (db_request_result_cp.next()) {
                        if (db_request_result_cp.value(0).toInt() == measurementQuery.value(2).toInt()) {
                            std::string cur_value = measurementQuery.value(3).toString().toStdString();
                            object->set_text(cur_value);

                            help_text = measurementQuery.value(1).toString().toStdString() + " (" +
                                        db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                            break;
                        }
                    }
                    break;
                }
            }
            db_request_result_cp.seek(0);
        } else if (object->get_type_object() == "Телеконтроль") {
            QSqlQuery controlQuery = dbManager.getControlObjects();
            while (controlQuery.next()) {
                if (controlQuery.value(0).toInt() == object->get_id()) {
                    object->set_text(controlQuery.value(3).toString().toStdString());
                    while (db_request_result_cp.next()) {
                        if (db_request_result_cp.value(0).toInt() == controlQuery.value(2).toInt()) {
                            help_text = controlQuery.value(1).toString().toStdString() + " (" +
                                        db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                            break;
                        }
                    }
                    break;
                }
            }
            db_request_result_cp.seek(0);
        } else if (object->get_type_object() == "Телесигнализация") {
            QSqlQuery signalQuery = dbManager.getSignalObjects();
            while (signalQuery.next()) {
                if (signalQuery.value(0).toInt() == object->get_id()) {
                    object->set_text(signalQuery.value(3).toString().toStdString());
                    while (db_request_result_cp.next()) {
                        if (db_request_result_cp.value(0).toInt() == signalQuery.value(2).toInt()) {
                            help_text = signalQuery.value(1).toString().toStdString() + " (" +
                                        db_request_result_cp.value(1).toString().toStdString() + ")";
                            object->set_help_text(help_text);
                            break;
                        }
                    }
                    break;
                }
            }
            db_request_result_cp.seek(0);
        }
    }

    QPixmap pix(scheme_params.width, scheme_params.height);
    QColor bgColor = {scheme_params.bgColor.red, scheme_params.bgColor.green, scheme_params.bgColor.blue};
    pix.fill(bgColor);

    QPainter *painter = new QPainter(&pix);

    Scheme scheme(scheme_params);
    scheme.draw_scheme(*painter);
    delete painter;
    scene->addPixmap(pix);
}


void MainView::updateTablelib() {
    DBManager &dbManager = DBManager::getInstance();
    bool success = dbManager.updateLibraryObject(
        this->lineEdit1->text(),
        this->lineEdit2->text().toInt(),
        this->lineEdit3->text().toInt(),
        this->lineEdit4->text().toInt(),
        this->lineEdit5->text().toInt(),
        cur_obj_id
    );

    if (success) {
        updateScene();
        newWindow->hide();
    } else {
        // Обработка ошибки, например:
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить объект библиотеки");
    }
}

void MainView::updateTablemes() {
    DBManager &dbManager = DBManager::getInstance();
    bool success = dbManager.updateMeasurement(
        this->lineEdit1->text(),
        this->lineEdit2->text().toInt(),
        this->lineEdit3->text().toDouble(),
        this->lineEdit4->text().toDouble(),
        this->lineEdit5->text().toDouble(),
        cur_obj_id
    );

    if (success) {
        updateScene();
        newWindow->hide();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить измерение");
    }
}

void MainView::updateTablecontrol() {
    DBManager &dbManager = DBManager::getInstance();
    bool success = dbManager.updateControl(
        this->lineEdit1->text(),
        this->lineEdit2->text().toInt(),
        cur_obj_id
    );

    if (success) {
        updateScene();
        newWindow->hide();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить объект управления");
    }
}

void MainView::updateTablesign() {
    DBManager &dbManager = DBManager::getInstance();
    bool success = dbManager.updateSignal(
        this->lineEdit1->text(),
        this->lineEdit2->text().toInt(),
        cur_obj_id
    );

    if (success) {
        updateScene();
        newWindow->hide();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось обновить сигнал");
    }
}
