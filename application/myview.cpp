#include "myview.h"
#include <iostream>
#include <QScrollBar>
#include <QDialog>
#include <QToolTip>
#include "db_lib/db_connection.h"
#include <sstream>
#include <iomanip>
#include <QTableWidget>

MyView::MyView(QGraphicsScene* parent) : QGraphicsView(parent)
{
    // Подключаем слот, который будет отслеживать положение скроллбара
    scene = parent;
}

// void MyView::mouseDoubleClickEvent(QMouseEvent* event)
// {
//     if (event->button() == Qt::LeftButton)
//     {
//         QPoint point(event->pos().x(), event->pos().y());
//
//         for (auto object : scheme_params.objects_vector)
//         {
//             std::string tp_obj = object->get_type_object();
//             if (tp_obj == "Библиотечный объект")
//             {
//                 QPoint original_point = point;
//                 // Создаем объект преобразования
//                 QTransform transform;
//
//                 transform.translate(-1 * (object->get_x() + object->get_width() / 2),
//                                     -1 * (object->get_y() + object->get_height() / 2));
//
//
//                 //transform.rotate(-1 * object[4].toInt());
//
//                 // Применяем преобразование к точке
//                 QPoint newPoint = transform.map(point);
//
//                 if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
//                     newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
//                 {
//                     transform.reset();
//                     QSqlQuery db_request_result = connection_to_db_with_lib();
//
//                     QString name = "None";
//                     QString cp_id = "None";
//                     QString normal_state = "None";
//                     QString fail_state = "None";
//                     int cur_state = 0;
//                     this->cur_obj_id = object->get_id();
//
//                     while (db_request_result.next())
//                     {
//                         if (db_request_result.value(0).toInt() == object->get_id())
//                         {
//                             name = db_request_result.value(1).toString();
//                             cp_id = db_request_result.value(2).toString();
//                             normal_state = db_request_result.value(3).toString();
//                             fail_state = db_request_result.value(4).toString();
//                             cur_state = db_request_result.value(5).toInt();
//                         }
//                     }
//
//
//                     if (cur_state < (object->get_patterns().size() - 1))
//                     {
//                         cur_state += 1;
//                     }
//                     else
//                     {
//                         cur_state = 0;
//                     }
//                     update_table_lib(name, cp_id.toInt(),
//                                      normal_state.toInt(),
//                                      fail_state.toInt(), cur_state, cur_obj_id);
//                     updateScene();
//                 }
//             }
//         }
//     }
// }

void MyView::showOrderDialog(QPoint& point)
{
    ;
}


void MyView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // clickTimer->stop();

        QPoint point(event->pos().x(), event->pos().y());

        // showOrderDialog(point);

        for (auto object : scheme_params.objects_vector)
        {
            std::string tp_obj = object->get_type_object();
            if (tp_obj == "Библиотечный объект")
            {
                QPoint original_point = point;

                // Создаем объект преобразования
                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    transform.reset();

                    int hor_off = 30;
                    int ver_off = -30;

                    QDialog dialog(this);
                    dialog.setWindowTitle("Создание приказа");

                    dialog.setFixedSize(400, 300);

                    dialog.move(event->globalX() + hor_off, event->globalY() + ver_off);
                    QSqlQuery db_request_result = connection_to_db_with_lib();
                    QSqlQuery db_request_result_cp = connection_to_cp_db();

                    QString id = "None";
                    QString name = "None";
                    QString cp_id = "None";
                    QString normal_state = "None";
                    QString fail_state = "None";
                    QString cur_state = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";

                    this->cur_obj_id = object->get_id();

                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
                            id = db_request_result.value(0).toString();
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            normal_state = db_request_result.value(3).toString();
                            fail_state = db_request_result.value(4).toString();
                            cur_state = db_request_result.value(5).toString();
                            obj_type = db_request_result.value(6).toString();
                            obj_name = db_request_result.value(7).toString();

                            while (db_request_result_cp.next())
                            {
                                if (db_request_result_cp.value(0).toString() == cp_id)
                                {
                                    if (db_request_result_cp.value(1).toString() == "None")
                                    {
                                        cp_name = db_request_result_cp.value(1).toString();
                                    }
                                    else
                                    {
                                        cp_name = db_request_result_cp.value(2).toString() + " " + db_request_result_cp.
                                            value(1).toString();;
                                    }
                                }
                            }
                        }
                    }

                    QVBoxLayout* layout = new QVBoxLayout(&dialog);

                    QLabel* label = new QLabel(QString("Объект: %1").arg(name));
                    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    layout->addWidget(label);

                    label = new QLabel(QString("Наим. контрольного пункта: %1").arg(cp_name));
                    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    layout->addWidget(label);

                    label = new QLabel(QString("Нормальное состояние объекта: %1").arg(normal_state));
                    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    layout->addWidget(label);

                    label = new QLabel(QString("Cостояние объекта при неисправности: %1").arg(fail_state));
                    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    layout->addWidget(label);

                    label = new QLabel(QString("Текущее состояние объекта: %1").arg(cur_state));
                    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
                    layout->addWidget(label);

                    QPushButton* createOrderButton = new QPushButton("Создать приказ");
                    layout->addWidget(createOrderButton);

                    QLabel* timerLabel = new QLabel();
                    QPushButton* cancelButton = new QPushButton("Отменить");
                    cancelButton->hide();

                    layout->addWidget(timerLabel);
                    layout->addWidget(cancelButton);

                    QTimer timer;
                    int remainingTime = 5;

                    connect(createOrderButton, &QPushButton::clicked, [&]()
                    {
                        createOrderButton->setEnabled(false);
                        cancelButton->show();
                        timer.start(1000);
                    });

                    connect(&timer, &QTimer::timeout, [&]()
                    {
                        --remainingTime;
                        timerLabel->setText(QString("Время до отправки приказа: %1").arg(remainingTime));

                        if (remainingTime == 0)
                        {
                            timer.stop();

                            int state = !cur_state.toInt();

                            update_table_lib_short(state, id.toInt());

                            timerLabel->setText("Приказ отправлен");
                            cancelButton->hide();
                        }
                    });

                    connect(cancelButton, &QPushButton::clicked, [&]()
                    {
                        timer.stop();
                        timerLabel->setText("Приказ отменен");
                    });

                    dialog.exec();
                }
            }
        }
    }
}

// void MyView::handleSingleClick(QMouseEvent* event)
// {
//
// }


void MyView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        // if (!clickTimer->isActive())
        // {
        //     //lastClickPos = QPoint(event->pos().x(), event->pos().y());
        //     lastEvent = event;
        //     clickTimer->start(250);
        // }

        QPoint point(event->pos().x(), event->pos().y());

        for (auto object : scheme_params.objects_vector)
        {
            std::string tp_obj = object->get_type_object();
            QPoint original_point = point;
            // Создаем объект преобразования
            QTransform transform;

            transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                -1 * (object->get_y() + object->get_height() / 2));

            //transform.rotate(-1 * object[4].toInt());

            // Применяем преобразование к точке
            QPoint newPoint = transform.map(point);
            if (object->get_show_help())
            {
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    transform.reset();

                    newWindow = new QMenu();
                    newWindow->move(event->globalX(), event->globalY());

                    QVBoxLayout* mainLayout = new QVBoxLayout(newWindow);
                    QLabel* label1 = new QLabel(
                        QTextCodec::codecForName("cp1251")->toUnicode(object->get_help_text().c_str()));
                    mainLayout->addWidget(label1);
                    label1->adjustSize();
                    newWindow->show();
                }
            }
        }
    }

    else if (event->button() == Qt::RightButton)
    {
        QPoint point(event->pos().x(), event->pos().y());

        for (auto object : scheme_params.objects_vector)
        {
            std::string tp_obj = object->get_type_object();
            if (tp_obj == "Библиотечный объект")
            {
                QPoint original_point = point;

                // Создаем объект преобразования
                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    transform.reset();

                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();
                    newWindow->setFixedWidth(270);

                    newWindow->move(event->globalX() + hor_off, event->globalY() + ver_off);
                    QSqlQuery db_request_result = connection_to_db_with_lib();
                    QSqlQuery db_request_result_cp = connection_to_cp_db();

                    QString id = "None";
                    QString name = "None";
                    QString cp_id = "None";
                    QString normal_state = "None";
                    QString fail_state = "None";
                    QString cur_state = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";
                    QSqlQuery cp_objects;

                    this->cur_obj_id = object->get_id();

                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
                            id = db_request_result.value(0).toString();
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            normal_state = db_request_result.value(3).toString();
                            fail_state = db_request_result.value(4).toString();
                            cur_state = db_request_result.value(5).toString();
                            obj_type = db_request_result.value(6).toString();
                            obj_name = db_request_result.value(7).toString();

                            cp_objects = get_all_cp_objects(cp_id.toInt());


                            while (db_request_result_cp.next())
                            {
                                if (db_request_result_cp.value(0).toString() == cp_id)
                                {
                                    if (db_request_result_cp.value(1).toString() == "None")
                                    {
                                        cp_name = db_request_result_cp.value(1).toString();
                                    }
                                    else
                                    {
                                        cp_name = db_request_result_cp.value(2).toString() + " " + db_request_result_cp.
                                            value(1).toString();;
                                    }
                                }
                            }
                        }
                    }


                    QVBoxLayout* mainLayout = new QVBoxLayout(newWindow);

                    QHBoxLayout* row1Layout = new QHBoxLayout();
                    QLabel* label1 = new QLabel("Наименование:");
                    QLabel* label1_1 = new QLabel(name);
                    label1_1->setStyleSheet("QLabel { color : blue; }");
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(label1_1);

                    QHBoxLayout* row2Layout = new QHBoxLayout();
                    QLabel* label2 = new QLabel("Идентификатор:");
                    QLabel* label2_2 = new QLabel(id);
                    label2_2->setStyleSheet("QLabel { color : blue; }");
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(label2_2);

                    QHBoxLayout* row3Layout = new QHBoxLayout();
                    QLabel* label3 = new QLabel("Текущее значение:");
                    QLabel* label3_3 = new QLabel(cur_state);
                    label3_3->setStyleSheet("QLabel { color : blue; }");
                    row3Layout->addWidget(label3);
                    row3Layout->addWidget(label3_3);

                    QHBoxLayout* row4Layout = new QHBoxLayout();
                    QLabel* label4 = new QLabel("Нормальное положение:");
                    QLabel* label4_4 = new QLabel(normal_state);
                    label4_4->setStyleSheet("QLabel { color : blue; }");
                    row4Layout->addWidget(label4);
                    row4Layout->addWidget(label4_4);
                    QHBoxLayout* row5Layout = new QHBoxLayout();
                    QLabel* label5 = new QLabel("Значение при ошибке:");
                    QLabel* label5_5 = new QLabel(fail_state);
                    label5_5->setStyleSheet("QLabel { color : blue; }");
                    row5Layout->addWidget(label5);
                    row5Layout->addWidget(label5_5);

                    QHBoxLayout* row6Layout = new QHBoxLayout();
                    QLabel* label6 = new QLabel("Наим. контр. пункта:");
                    QLabel* label6_6 = new QLabel(cp_name);
                    label6_6->setStyleSheet("QLabel { color : blue; }");
                    row6Layout->addWidget(label6);
                    row6Layout->addWidget(label6_6);

                    QHBoxLayout* row7Layout = new QHBoxLayout();
                    QLabel* label7 = new QLabel("Диспетчерское наименование:");
                    QLabel* label7_7 = new QLabel(obj_name);
                    label7_7->setStyleSheet("QLabel { color : blue; }");
                    row7Layout->addWidget(label7);
                    row7Layout->addWidget(label7_7);

                    QHBoxLayout* row8Layout = new QHBoxLayout();
                    QLabel* label8 = new QLabel("Тип объекта:");
                    QLabel* label8_8 = new QLabel(obj_type);
                    label8_8->setStyleSheet("QLabel { color : blue; }");
                    row8Layout->addWidget(label8);
                    row8Layout->addWidget(label8_8);

                    //QPushButton* saveButton = new QPushButton("&Сохранить");

                    //connect(saveButton, &QPushButton::clicked, this, &MyView::updateTablelib);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addLayout(row3Layout);
                    mainLayout->addLayout(row4Layout);
                    mainLayout->addLayout(row5Layout);
                    mainLayout->addLayout(row6Layout);
                    mainLayout->addLayout(row7Layout);


                    QTableWidget* table = new QTableWidget();

                    table->setColumnCount(2);
                    table->setHorizontalHeaderItem(0, new QTableWidgetItem("id объекта"));
                    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя объекта"));


                    // Заполняем таблицу данными
                    int row = 0;
                    while (cp_objects.next())
                    {
                        table->insertRow(row);
                        for (int col = 0; col < 2; ++col)
                        {
                            QTableWidgetItem* item = new QTableWidgetItem(cp_objects.value(col).toString());
                            table->setItem(row, col, item);
                        }
                        ++row;
                    }
                    if (table->rowCount() >= 7)
                    {
                        table->setFixedHeight(250);
                    }
                    table->setFixedWidth(256);
                    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


                    mainLayout->addLayout(row8Layout);

                    QHBoxLayout* row9Layout = new QHBoxLayout();
                    QLabel* label9 = new QLabel("Объекты этого контр. пункта:");
                    row9Layout->addWidget(label9);
                    mainLayout->addLayout(row9Layout);

                    QHBoxLayout* row10Layout = new QHBoxLayout();
                    row10Layout->addWidget(table);
                    mainLayout->addLayout(row10Layout);
                    //mainLayout->addWidget(saveButton);

                    newWindow->show();
                }
            }
            else if (tp_obj == "Телеизмерение")
            {
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();
                    newWindow->setFixedWidth(270);

                    newWindow->move(event->globalX() + hor_off, event->globalY() + ver_off);

                    QSqlQuery db_request_result = connection_to_db_with_measure();
                    QSqlQuery db_request_result_cp = connection_to_cp_db();

                    QString id = "None";
                    QString name = "None";
                    QString cp_id = "None";
                    QString cur_value = "None";
                    QString min_value = "None";
                    QString max_value = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";
                    QString n_l_l = "None";
                    QString n_u_l = "None";
                    QString c_l_l = "None";
                    QString c_u_l = "None";
                    QSqlQuery cp_objects;

                    this->cur_obj_id = object->get_id();

                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
                            id = db_request_result.value(0).toString();
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            cur_value = db_request_result.value(3).toString();
                            min_value = db_request_result.value(4).toString();
                            max_value = db_request_result.value(5).toString();
                            obj_type = db_request_result.value(6).toString();
                            obj_name = db_request_result.value(7).toString();
                            n_l_l = db_request_result.value(8).toString();
                            n_u_l = db_request_result.value(9).toString();
                            c_l_l = db_request_result.value(10).toString();
                            c_u_l = db_request_result.value(11).toString();

                            std::ostringstream oss;
                            oss << std::fixed << std::setprecision(2) << db_request_result.value(3).toDouble();
                            cur_value = QString::fromStdString(oss.str());

                            std::ostringstream oss1;
                            oss1 << std::fixed << std::setprecision(2) << db_request_result.value(4).toDouble();
                            min_value = QString::fromStdString(oss1.str());

                            std::ostringstream oss2;
                            oss2 << std::fixed << std::setprecision(2) << db_request_result.value(5).toDouble();
                            max_value = QString::fromStdString(oss2.str());

                            cp_objects = get_all_cp_objects(cp_id.toInt());


                            while (db_request_result_cp.next())
                            {
                                if (db_request_result_cp.value(0).toString() == cp_id)
                                {
                                    if (db_request_result_cp.value(1).toString() == "None")
                                    {
                                        cp_name = db_request_result_cp.value(1).toString();
                                    }
                                    else
                                    {
                                        cp_name = db_request_result_cp.value(2).toString() + " " + db_request_result_cp.
                                            value(1).toString();;
                                    }
                                }
                            }
                        }
                    }


                    QVBoxLayout* mainLayout = new QVBoxLayout(newWindow);
                    QHBoxLayout* row1Layout = new QHBoxLayout();
                    QLabel* label1 = new QLabel("Наименование:");
                    QLabel* label1_1 = new QLabel(name);
                    label1_1->setStyleSheet("QLabel { color : blue; }");
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(label1_1);

                    QHBoxLayout* row2Layout = new QHBoxLayout();
                    QLabel* label2 = new QLabel("Идентификатор:");
                    QLabel* label2_2 = new QLabel(id);
                    label2_2->setStyleSheet("QLabel { color : blue; }");
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(label2_2);

                    QHBoxLayout* row3Layout = new QHBoxLayout();
                    QLabel* label3 = new QLabel("Текущее значение:");
                    QLabel* label3_3 = new QLabel(cur_value);
                    label3_3->setStyleSheet("QLabel { color : blue; }");
                    row3Layout->addWidget(label3);
                    row3Layout->addWidget(label3_3);

                    QHBoxLayout* row4Layout = new QHBoxLayout();
                    QLabel* label4 = new QLabel("Минимальное значение:");
                    QLabel* label4_4 = new QLabel(min_value);
                    label4_4->setStyleSheet("QLabel { color : blue; }");
                    row4Layout->addWidget(label4);
                    row4Layout->addWidget(label4_4);

                    QHBoxLayout* row5Layout = new QHBoxLayout();
                    QLabel* label5 = new QLabel("Максимальное значение:");
                    QLabel* label5_5 = new QLabel(max_value);
                    label5_5->setStyleSheet("QLabel { color : blue; }");
                    row5Layout->addWidget(label5);
                    row5Layout->addWidget(label5_5);

                    QHBoxLayout* row6Layout = new QHBoxLayout();
                    QLabel* label6 = new QLabel("Наим. контр. пункта:");
                    QLabel* label6_6 = new QLabel(cp_name);
                    label6_6->setStyleSheet("QLabel { color : blue; }");
                    row6Layout->addWidget(label6);
                    row6Layout->addWidget(label6_6);

                    QHBoxLayout* row7Layout = new QHBoxLayout();
                    QLabel* label7 = new QLabel("Диспетчерское наименование:");
                    QLabel* label7_7 = new QLabel(obj_name);
                    label7_7->setStyleSheet("QLabel { color : blue; }");
                    row7Layout->addWidget(label7);
                    row7Layout->addWidget(label7_7);

                    QHBoxLayout* row8Layout = new QHBoxLayout();
                    QLabel* label8 = new QLabel("Тип объекта:");
                    QLabel* label8_8 = new QLabel(obj_type);
                    label8_8->setStyleSheet("QLabel { color : blue; }");
                    row8Layout->addWidget(label8);
                    row8Layout->addWidget(label8_8);

                    QHBoxLayout* row9Layout = new QHBoxLayout();
                    QLabel* label9 = new QLabel("Макс. нормальное отклон.:");
                    QLabel* label9_9 = new QLabel(n_u_l);
                    label9_9->setStyleSheet("QLabel { color : blue; }");
                    row9Layout->addWidget(label9);
                    row9Layout->addWidget(label9_9);

                    QHBoxLayout* row10Layout = new QHBoxLayout();
                    QLabel* label10 = new QLabel("Мин. нормальное отклон.:");
                    QLabel* label10_10 = new QLabel(n_l_l);
                    label10_10->setStyleSheet("QLabel { color : blue; }");
                    row10Layout->addWidget(label10);
                    row10Layout->addWidget(label10_10);

                    QHBoxLayout* row11Layout = new QHBoxLayout();
                    QLabel* label11 = new QLabel("Макс. предельное отклон.:");
                    QLabel* label11_11 = new QLabel(c_u_l);
                    label11_11->setStyleSheet("QLabel { color : blue; }");
                    row11Layout->addWidget(label11);
                    row11Layout->addWidget(label11_11);

                    QHBoxLayout* row12Layout = new QHBoxLayout();
                    QLabel* label12 = new QLabel("Мин. предельное отклон.:");
                    QLabel* label12_12 = new QLabel(c_l_l);
                    label12_12->setStyleSheet("QLabel { color : blue; }");
                    row12Layout->addWidget(label12);
                    row12Layout->addWidget(label12_12);

                    //QPushButton* saveButton = new QPushButton("&Сохранить");

                    //connect(saveButton, &QPushButton::clicked, this, &MyView::updateTablemes);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addLayout(row3Layout);
                    mainLayout->addLayout(row4Layout);
                    mainLayout->addLayout(row5Layout);
                    mainLayout->addLayout(row6Layout);
                    mainLayout->addLayout(row7Layout);
                    mainLayout->addLayout(row8Layout);
                    mainLayout->addLayout(row9Layout);
                    mainLayout->addLayout(row10Layout);
                    mainLayout->addLayout(row11Layout);
                    mainLayout->addLayout(row12Layout);
                    //mainLayout->addWidget(saveButton);


                    QTableWidget* table = new QTableWidget();

                    table->setColumnCount(2);
                    table->setHorizontalHeaderItem(0, new QTableWidgetItem("id объекта"));
                    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя объекта"));


                    // Заполняем таблицу данными
                    int row = 0;
                    while (cp_objects.next())
                    {
                        table->insertRow(row);
                        for (int col = 0; col < 2; ++col)
                        {
                            QTableWidgetItem* item = new QTableWidgetItem(cp_objects.value(col).toString());
                            table->setItem(row, col, item);
                        }
                        ++row;
                    }
                    if (table->rowCount() >= 7)
                    {
                        table->setFixedHeight(250);
                    }
                    table->setFixedWidth(256);
                    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

                    QHBoxLayout* row13Layout = new QHBoxLayout();
                    QLabel* label13 = new QLabel("Объекты этого контр. пункта:");
                    row13Layout->addWidget(label13);
                    mainLayout->addLayout(row13Layout);

                    QHBoxLayout* row14Layout = new QHBoxLayout();
                    row14Layout->addWidget(table);
                    mainLayout->addLayout(row14Layout);

                    newWindow->show();
                }
            }
            else if (tp_obj == "Телеконтроль")
            {
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));


                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();
                    newWindow->setFixedWidth(260);

                    newWindow->move(event->globalX() + hor_off, event->globalY() + ver_off);

                    QSqlQuery db_request_result = connection_to_db_with_control();
                    QSqlQuery db_request_result_cp = connection_to_cp_db();

                    QString name = "None";
                    QString cp_id = "None";
                    QString id = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";
                    QSqlQuery cp_objects;

                    this->cur_obj_id = object->get_id();
                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            id = db_request_result.value(0).toString();
                            obj_type = db_request_result.value(6).toString();
                            obj_name = db_request_result.value(7).toString();

                            cp_objects = get_all_cp_objects(cp_id.toInt());

                            while (db_request_result_cp.next())
                            {
                                if (db_request_result_cp.value(0).toString() == cp_id)
                                {
                                    if (db_request_result_cp.value(1).toString() == "None")
                                    {
                                        cp_name = db_request_result_cp.value(1).toString();
                                    }
                                    else
                                    {
                                        cp_name = db_request_result_cp.value(2).toString() + " " + db_request_result_cp.
                                            value(1).toString();;
                                    }
                                }
                            };
                        }
                    }


                    QVBoxLayout* mainLayout = new QVBoxLayout(newWindow);

                    QHBoxLayout* row1Layout = new QHBoxLayout();
                    QLabel* label1 = new QLabel("Наименование:");
                    QLabel* label1_1 = new QLabel(name);
                    label1_1->setStyleSheet("QLabel { color : blue; }");
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(label1_1);

                    QHBoxLayout* row2Layout = new QHBoxLayout();
                    QLabel* label2 = new QLabel("Идентификатор:");
                    QLabel* label2_2 = new QLabel(id);
                    label2_2->setStyleSheet("QLabel { color : blue; }");
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(label2_2);

                    QHBoxLayout* row6Layout = new QHBoxLayout();
                    QLabel* label6 = new QLabel("Наим. контр. пункта:");
                    QLabel* label6_6 = new QLabel(cp_name);
                    label6_6->setStyleSheet("QLabel { color : blue; }");
                    row6Layout->addWidget(label6);
                    row6Layout->addWidget(label6_6);

                    QHBoxLayout* row7Layout = new QHBoxLayout();
                    QLabel* label7 = new QLabel("Диспетчерское наименование:");
                    QLabel* label7_7 = new QLabel(obj_name);
                    label7_7->setStyleSheet("QLabel { color : blue; }");
                    row7Layout->addWidget(label7);
                    row7Layout->addWidget(label7_7);

                    QHBoxLayout* row8Layout = new QHBoxLayout();
                    QLabel* label8 = new QLabel("Тип объекта:");
                    QLabel* label8_8 = new QLabel(obj_type);
                    label8_8->setStyleSheet("QLabel { color : blue; }");
                    row8Layout->addWidget(label8);
                    row8Layout->addWidget(label8_8);


                    //QPushButton* saveButton = new QPushButton("&Сохранить");

                    //connect(saveButton, &QPushButton::clicked, this, &MyView::updateTablecontrol);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addLayout(row6Layout);
                    mainLayout->addLayout(row7Layout);
                    mainLayout->addLayout(row8Layout);
                    //mainLayout->addWidget(saveButton);

                    QTableWidget* table = new QTableWidget();

                    table->setColumnCount(2);
                    table->setHorizontalHeaderItem(0, new QTableWidgetItem("id объекта"));
                    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя объекта"));


                    // Заполняем таблицу данными
                    int row = 0;
                    while (cp_objects.next())
                    {
                        table->insertRow(row);
                        for (int col = 0; col < 2; ++col)
                        {
                            QTableWidgetItem* item = new QTableWidgetItem(cp_objects.value(col).toString());
                            table->setItem(row, col, item);
                        }
                        ++row;
                    }
                    if (table->rowCount() >= 7)
                    {
                        table->setFixedHeight(250);
                    }
                    table->setFixedWidth(256);
                    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

                    QHBoxLayout* row13Layout = new QHBoxLayout();
                    QLabel* label13 = new QLabel("Объекты этого контр. пункта:");
                    row13Layout->addWidget(label13);
                    mainLayout->addLayout(row13Layout);

                    QHBoxLayout* row14Layout = new QHBoxLayout();
                    row14Layout->addWidget(table);
                    mainLayout->addLayout(row14Layout);

                    newWindow->show();
                }
            }
            else if (tp_obj == "Телесигнализация")
            {
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;
                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));


                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);
                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();
                    newWindow->setFixedWidth(260);

                    newWindow->move(event->globalX() + hor_off, event->globalY() + ver_off);

                    QSqlQuery db_request_result = connection_to_db_with_signal();
                    QSqlQuery db_request_result_cp = connection_to_cp_db();

                    QString name = "None";
                    QString cp_id = "None";
                    QString id = "None";
                    QString cp_name = "None";
                    QString obj_type = "None";
                    QString obj_name = "None";
                    QSqlQuery cp_objects;

                    this->cur_obj_id = object->get_id();
                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            id = db_request_result.value(0).toString();
                            obj_type = db_request_result.value(3).toString();
                            obj_name = db_request_result.value(4).toString();
                            cp_objects = get_all_cp_objects(cp_id.toInt());

                            while (db_request_result_cp.next())
                            {
                                if (db_request_result_cp.value(0).toString() == cp_id)
                                {
                                    if (db_request_result_cp.value(1).toString() == "None")
                                    {
                                        cp_name = db_request_result_cp.value(1).toString();
                                    }
                                    else
                                    {
                                        cp_name = db_request_result_cp.value(2).toString() + " " + db_request_result_cp.
                                            value(1).toString();;
                                    }
                                }
                            }
                        }
                    }


                    QVBoxLayout* mainLayout = new QVBoxLayout(newWindow);

                    QHBoxLayout* row1Layout = new QHBoxLayout();
                    QLabel* label1 = new QLabel("Наименование:");
                    QLabel* label1_1 = new QLabel(name);
                    label1_1->setStyleSheet("QLabel { color : blue; }");
                    row1Layout->addWidget(label1);
                    row1Layout->addWidget(label1_1);

                    QHBoxLayout* row2Layout = new QHBoxLayout();
                    QLabel* label2 = new QLabel("Идентификатор:");
                    QLabel* label2_2 = new QLabel(id);
                    label2_2->setStyleSheet("QLabel { color : blue; }");
                    row2Layout->addWidget(label2);
                    row2Layout->addWidget(label2_2);

                    QHBoxLayout* row6Layout = new QHBoxLayout();
                    QLabel* label6 = new QLabel("Наим. контр. пункта:");
                    QLabel* label6_6 = new QLabel(cp_name);
                    label6_6->setStyleSheet("QLabel { color : blue; }");
                    row6Layout->addWidget(label6);
                    row6Layout->addWidget(label6_6);

                    QHBoxLayout* row7Layout = new QHBoxLayout();
                    QLabel* label7 = new QLabel("Диспетчерское наименование:");
                    QLabel* label7_7 = new QLabel(obj_name);
                    label7_7->setStyleSheet("QLabel { color : blue; }");
                    row7Layout->addWidget(label7);
                    row7Layout->addWidget(label7_7);

                    QHBoxLayout* row8Layout = new QHBoxLayout();
                    QLabel* label8 = new QLabel("Тип объекта:");
                    QLabel* label8_8 = new QLabel(obj_type);
                    label8_8->setStyleSheet("QLabel { color : blue; }");
                    row8Layout->addWidget(label8);
                    row8Layout->addWidget(label8_8);


                    //QPushButton* saveButton = new QPushButton("&Сохранить");

                    //connect(saveButton, &QPushButton::clicked, this, &MyView::updateTablecontrol);

                    mainLayout->addLayout(row1Layout);
                    mainLayout->addLayout(row2Layout);
                    mainLayout->addLayout(row6Layout);
                    mainLayout->addLayout(row7Layout);
                    mainLayout->addLayout(row8Layout);

                    QTableWidget* table = new QTableWidget();

                    table->setColumnCount(2);
                    table->setHorizontalHeaderItem(0, new QTableWidgetItem("id объекта"));
                    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Имя объекта"));


                    // Заполняем таблицу данными
                    int row = 0;
                    while (cp_objects.next())
                    {
                        table->insertRow(row);
                        for (int col = 0; col < 2; ++col)
                        {
                            QTableWidgetItem* item = new QTableWidgetItem(cp_objects.value(col).toString());
                            table->setItem(row, col, item);
                        }
                        ++row;
                    }
                    if (table->rowCount() >= 7)
                    {
                        table->setFixedHeight(250);
                    }
                    table->setFixedWidth(256);
                    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

                    QHBoxLayout* row13Layout = new QHBoxLayout();
                    QLabel* label13 = new QLabel("Объекты этого контр. пункта:");
                    row13Layout->addWidget(label13);
                    mainLayout->addLayout(row13Layout);

                    QHBoxLayout* row14Layout = new QHBoxLayout();
                    row14Layout->addWidget(table);
                    mainLayout->addLayout(row14Layout);
                    //mainLayout->addWidget(saveButton);

                    newWindow->show();
                }
            }
        }
    }
}


void MyView::updateScene()
{
    QSqlQuery db_request_result = connection_to_db();
    QSqlQuery db_request_result_cp = connection_to_cp_db();
    std::string help_text;

    for (auto object : scheme_params.objects_vector)
    {
        if (object->get_type_object() == "Библиотечный объект")
        {
            while (db_request_result.next())
            {
                if (db_request_result.value(0).toInt() == object->get_id())
                {
                    object->set_condition(db_request_result.value(2).toInt());
                    while (db_request_result_cp.next())
                    {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt())
                        {
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
        }
        else if (object->get_type_object() == "Телеизмерение")
        {
            while (db_request_result.next())
            {
                if (db_request_result.value(0).toInt() == object->get_id())
                {
                    object->set_text(db_request_result.value(3).toString().toStdString());
                    while (db_request_result_cp.next())
                    {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt())
                        {
                            std::string cur_value = db_request_result.value(4).toString().toStdString();
                            object->set_text(cur_value);

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
        }
        else if (object->get_type_object() == "Телеконтроль")
        {
            while (db_request_result.next())
            {
                if (db_request_result.value(0).toInt() == object->get_id())
                {
                    object->set_text(db_request_result.value(3).toString().toStdString());
                    while (db_request_result_cp.next())
                    {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt())
                        {
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
        }
        else if (object->get_type_object() == "Телесигнализация")
        {
            while (db_request_result.next())
            {
                if (db_request_result.value(0).toInt() == object->get_id())
                {
                    object->set_text(db_request_result.value(3).toString().toStdString());
                    while (db_request_result_cp.next())
                    {
                        if (db_request_result_cp.value(0).toInt() == db_request_result.value(4).toInt())
                        {
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
        }
    }

    QPixmap pix(scheme_params.width, scheme_params.height);
    QColor bgColor = {scheme_params.bgColor.red, scheme_params.bgColor.green, scheme_params.bgColor.blue};
    pix.fill(bgColor);

    QPainter* painter = new QPainter(&pix);

    Scheme scheme(scheme_params);
    scheme.draw_scheme(*painter);
    delete painter;
    scene->addPixmap(pix);
}


void MyView::updateTablelib()
{
    update_table_lib(this->lineEdit1->text(), this->lineEdit2->text().toInt(), this->lineEdit3->text().toInt(),
                     this->lineEdit4->text().toInt(), this->lineEdit5->text().toInt(), cur_obj_id);
    updateScene();
    newWindow->hide();
}

void MyView::updateTablemes()
{
    update_table_mes(this->lineEdit1->text(), this->lineEdit2->text().toInt(), this->lineEdit3->text().toDouble(),
                     this->lineEdit4->text().toDouble(), this->lineEdit5->text().toDouble(), cur_obj_id);
    updateScene();
    newWindow->hide();
}

void MyView::updateTablecontrol()
{
    update_table_control(this->lineEdit1->text(), this->lineEdit2->text().toInt(), cur_obj_id);
    updateScene();
    newWindow->hide();
}

void MyView::updateTablesign()
{
    update_table_sign(this->lineEdit1->text(), this->lineEdit2->text().toInt(), cur_obj_id);
    updateScene();
    newWindow->hide();
}
