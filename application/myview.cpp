#include "myview.h"
#include <iostream>
#include <QScrollBar>
#include "db_lib/myview_connection.h"

MyView::MyView(QGraphicsScene* parent) : QGraphicsView(parent) {
    // Подключаем слот, который будет отслеживать положение скроллбара
}

void MyView::mouseDoubleClickEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        qDebug() << event->pos().x() << " " << event->pos().y();
        QPoint point(event->pos().x(), event->pos().y());
        qDebug() << "Начальные координаты точки:" << point;

        QFile file("/home/chekhov/github/ARMEditor/application/save.dat");
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Не удалось открыть файл для чтения";
            exit(0);
        }

        // Читаем QVector из файла
        QDataStream in(&file);
        QVector<QVector<QVariant> > qtVector;
        in.setVersion(QDataStream::Qt_5_11);
        in >> qtVector;

        this->vec = qtVector;


        file.close();

        for (auto object: qtVector) {
            std::string tp_obj = object[7].toString().toStdString();
            if (tp_obj == "Библиотечный объект") {
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;

                transform.translate(-1 * (object[0].toInt() + object[2].toInt() / 2),
                                    -1 * (object[1].toInt() + object[3].toInt() / 2));


                //transform.rotate(-1 * object[4].toInt());

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);

                if (newPoint.x() >= (-1 * object[2].toInt() / 2) && newPoint.x() <= object[2].toInt() / 2 &&
                    newPoint.y() >= (-1 * object[3].toInt() / 2) && newPoint.y() <= object[3].toInt() / 2) {
                    qDebug() << "Find it";
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();

                    newWindow->move(event->pos().x() + hor_off, event->pos().y() + ver_off);

                    qDebug() << object[5].toInt() << "Id";

                    QSqlQuery db_request_result = connection_to_db_with_lib();

                    QString name = "None";
                    QString cp_id = "None";
                    QString normal_state = "None";
                    QString fail_state = "None";
                    QString cur_state = "None";
                    this->cur_obj_id = object[5].toInt();

                    while (db_request_result.next()) {
                        if (db_request_result.value(0).toInt() == object[5].toInt()) {
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            normal_state = db_request_result.value(3).toString();
                            fail_state = db_request_result.value(4).toString();
                            cur_state = db_request_result.value(5).toString();

                            qDebug() << name << cp_id << normal_state << fail_state << cur_state;
                        }
                    }

                    QVBoxLayout* mainLayout = new QVBoxLayout(newWindow);

                    QHBoxLayout* row1Layout = new QHBoxLayout();
                    QLabel* label1 = new QLabel("Имя:");
                    lineEdit1 = new QLineEdit();
                    lineEdit1->setText(name);
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(lineEdit1);

                    QHBoxLayout* row2Layout = new QHBoxLayout();
                    QLabel* label2 = new QLabel("ЦП id:");
                    lineEdit2 = new QLineEdit();
                    lineEdit2->setText(cp_id);
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(lineEdit2);

                    QHBoxLayout* row3Layout = new QHBoxLayout();
                    QLabel* label3 = new QLabel("Нормальное значение:");
                    lineEdit3 = new QLineEdit();
                    lineEdit3->setText(normal_state);
                    row3Layout->addWidget(label3);
                    row3Layout->addWidget(lineEdit3);

                    QHBoxLayout* row4Layout = new QHBoxLayout();
                    QLabel* label4 = new QLabel("Значение при ошибке:");
                    lineEdit4 = new QLineEdit();
                    lineEdit4->setText(fail_state);
                    row4Layout->addWidget(label4);
                    row4Layout->addWidget(lineEdit4);

                    QHBoxLayout* row5Layout = new QHBoxLayout();
                    QLabel* label5 = new QLabel("Текущее значение:");
                    lineEdit5 = new QLineEdit();
                    lineEdit5->setText(cur_state);
                    row5Layout->addWidget(label5);
                    row5Layout->addWidget(lineEdit5);

                    QPushButton* saveButton = new QPushButton("&Сохранить");

                    connect(saveButton, &QPushButton::clicked, this, &MyView::updateTablelib);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addLayout(row3Layout);
                    mainLayout->addLayout(row4Layout);
                    mainLayout->addLayout(row5Layout);
                    mainLayout->addWidget(saveButton);

                    newWindow->show();
                }

                //ebug() << "Новые координаты точки:" << newPoint;
            } else if (tp_obj == "Телеизмерение") {
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;

                transform.translate(-1 * (object[0].toInt() + object[2].toInt() / 2),
                                    -1 * (object[1].toInt() + object[3].toInt() / 2));


                //transform.rotate(-1 * object[4].toInt());

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);

                if (newPoint.x() >= (-1 * object[2].toInt() / 2) && newPoint.x() <= object[2].toInt() / 2 &&
                    newPoint.y() >= (-1 * object[3].toInt() / 2) && newPoint.y() <= object[3].toInt() / 2) {
                    qDebug() << "Find it";
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();

                    newWindow->move(event->pos().x() + hor_off, event->pos().y() + ver_off);

                    qDebug() << object[5].toInt() << "Id";

                    QSqlQuery db_request_result = connection_to_db_with_measure();

                    QString name = "None";
                    QString cp_id = "None";
                    QString cur_value = "None";
                    QString min_value = "None";
                    QString max_value = "None";

                    this->cur_obj_id = object[5].toInt();

                    while (db_request_result.next()) {
                        if (db_request_result.value(0).toInt() == object[5].toInt()) {
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            cur_value = db_request_result.value(3).toString();
                            min_value = db_request_result.value(4).toString();
                            max_value = db_request_result.value(5).toString();

                            qDebug() << name << cp_id << cur_value << min_value << max_value;
                        }
                    }


                    QVBoxLayout* mainLayout = new QVBoxLayout(newWindow);

                    QHBoxLayout* row1Layout = new QHBoxLayout();
                    QLabel* label1 = new QLabel("Имя:");
                    lineEdit1 = new QLineEdit();
                    lineEdit1->setText(name);
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(lineEdit1);

                    QHBoxLayout* row2Layout = new QHBoxLayout();
                    QLabel* label2 = new QLabel("ЦП id:");
                    lineEdit2 = new QLineEdit();
                    lineEdit2->setText(cp_id);
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(lineEdit2);

                    QHBoxLayout* row3Layout = new QHBoxLayout();
                    QLabel* label3 = new QLabel("Текущее значение:");
                    lineEdit3 = new QLineEdit();
                    lineEdit3->setText(cur_value);
                    row3Layout->addWidget(label3);
                    row3Layout->addWidget(lineEdit3);

                    QHBoxLayout* row4Layout = new QHBoxLayout();
                    QLabel* label4 = new QLabel("Минимальное значение:");
                    lineEdit4 = new QLineEdit();
                    lineEdit4->setText(min_value);
                    row4Layout->addWidget(label4);
                    row4Layout->addWidget(lineEdit4);

                    QHBoxLayout* row5Layout = new QHBoxLayout();
                    QLabel* label5 = new QLabel("Максимальное значение:");
                    lineEdit5 = new QLineEdit();
                    lineEdit5->setText(max_value);
                    row5Layout->addWidget(label5);
                    row5Layout->addWidget(lineEdit5);

                    QPushButton* saveButton = new QPushButton("&Сохранить");

                    connect(saveButton, &QPushButton::clicked, this, &MyView::updateTablemes);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addLayout(row3Layout);
                    mainLayout->addLayout(row4Layout);
                    mainLayout->addLayout(row5Layout);
                    mainLayout->addWidget(saveButton);

                    newWindow->show();
                }
            } else if (tp_obj == "Телеконтроль") {
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;

                transform.translate(-1 * (object[0].toInt() + object[2].toInt() / 2),
                                    -1 * (object[1].toInt() + object[3].toInt() / 2));


                //transform.rotate(-1 * object[4].toInt());

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);

                if (newPoint.x() >= (-1 * object[2].toInt() / 2) && newPoint.x() <= object[2].toInt() / 2 &&
                    newPoint.y() >= (-1 * object[3].toInt() / 2) && newPoint.y() <= object[3].toInt() / 2) {
                    qDebug() << "Find it";
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();

                    newWindow->move(event->pos().x() + hor_off, event->pos().y() + ver_off);

                    qDebug() << object[5].toInt() << "Id";

                    QSqlQuery db_request_result = connection_to_db_with_control();

                    QString name = "None";
                    QString cp_id = "None";

                    this->cur_obj_id = object[5].toInt();

                    while (db_request_result.next()) {
                        if (db_request_result.value(0).toInt() == object[5].toInt()) {
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();

                            qDebug() << name << cp_id;
                        }
                    }


                    QVBoxLayout* mainLayout = new QVBoxLayout(newWindow);

                    QHBoxLayout* row1Layout = new QHBoxLayout();
                    QLabel* label1 = new QLabel("Имя:");
                    lineEdit1 = new QLineEdit();
                    lineEdit1->setText(name);
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(lineEdit1);

                    QHBoxLayout* row2Layout = new QHBoxLayout();
                    QLabel* label2 = new QLabel("ЦП id:");
                    lineEdit2 = new QLineEdit();
                    lineEdit2->setText(cp_id);
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(lineEdit2);


                    QPushButton* saveButton = new QPushButton("&Сохранить");

                    connect(saveButton, &QPushButton::clicked, this, &MyView::updateTablecontrol);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addWidget(saveButton);

                    newWindow->show();
                }
            } else if (tp_obj == "Телесигнализация") {
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;

                transform.translate(-1 * (object[0].toInt() + object[2].toInt() / 2),
                                    -1 * (object[1].toInt() + object[3].toInt() / 2));


                //transform.rotate(-1 * object[4].toInt());

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);

                if (newPoint.x() >= (-1 * object[2].toInt() / 2) && newPoint.x() <= object[2].toInt() / 2 &&
                    newPoint.y() >= (-1 * object[3].toInt() / 2) && newPoint.y() <= object[3].toInt() / 2) {
                    qDebug() << "Find it";
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();

                    newWindow->move(event->pos().x() + hor_off, event->pos().y() + ver_off);

                    qDebug() << object[5].toInt() << "Id";

                    QSqlQuery db_request_result = connection_to_db_with_signal();

                    QString name = "";
                    QString cp_id = "";

                    this->cur_obj_id = object[5].toInt();

                    while (db_request_result.next()) {
                        if (db_request_result.value(0).toInt() == object[5].toInt()) {
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();

                            qDebug() << name << cp_id;
                        }
                    }


                    QVBoxLayout* mainLayout = new QVBoxLayout(newWindow);

                    QHBoxLayout* row1Layout = new QHBoxLayout();
                    QLabel* label1 = new QLabel("Имя:");
                    lineEdit1 = new QLineEdit();
                    lineEdit1->setText(name);
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(lineEdit1);

                    QHBoxLayout* row2Layout = new QHBoxLayout();
                    QLabel* label2 = new QLabel("ЦП id:");
                    lineEdit2 = new QLineEdit();
                    lineEdit2->setText(cp_id);
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(lineEdit2);

                    QPushButton* saveButton = new QPushButton("&Сохранить");

                    connect(saveButton, &QPushButton::clicked, this, &MyView::updateTablesign);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addWidget(saveButton);

                    newWindow->show();
                }
            }
        }
    }
}


void MyView::updateTablelib() {
    qDebug() << "update";
    update_table_lib(this->lineEdit1->text(), this->lineEdit2->text().toInt(), this->lineEdit3->text().toInt(),
                     this->lineEdit4->text().toInt(), this->lineEdit5->text().toInt(), cur_obj_id);
    newWindow->hide();

}

void MyView::updateTablemes() {
    qDebug() << "update";
    update_table_mes(this->lineEdit1->text(), this->lineEdit2->text().toInt(), this->lineEdit3->text().toDouble(),
                     this->lineEdit4->text().toDouble(), this->lineEdit5->text().toDouble(), cur_obj_id);
    newWindow->hide();
}

void MyView::updateTablecontrol() {
    qDebug() << "update";
    update_table_control(this->lineEdit1->text(), this->lineEdit2->text().toInt(), cur_obj_id);
    newWindow->hide();
}

void MyView::updateTablesign() {
    qDebug() << "update";
    update_table_sign(this->lineEdit1->text(), this->lineEdit2->text().toInt(), cur_obj_id);
    newWindow->hide();
}
