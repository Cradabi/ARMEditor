#include "myview.h"
#include <iostream>
#include <QScrollBar>
#include "db_lib/db_connection.h"

MyView::MyView(QGraphicsScene* parent) : QGraphicsView(parent)
{
    // Подключаем слот, который будет отслеживать положение скроллбара
    scene = parent;
}

void MyView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        qDebug() << event->pos().x() << " " << event->pos().y();
        QPoint point(event->pos().x(), event->pos().y());
        qDebug() << "Начальные координаты точки:" << point;

        for (auto object : scheme_params.objects_vector)
        {
            std::string tp_obj = object->get_type_object();
            // qDebug() << tp_obj;
            if (tp_obj == "Библиотечный объект")
            {
                qDebug() << "Библиотечный объект";
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;

                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));


                //transform.rotate(-1 * object[4].toInt());

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);

                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    qDebug() << "Find it";

                    transform.reset();

                    qDebug() << object->get_id() << "Id";

                    QSqlQuery db_request_result = connection_to_db_with_lib();

                    QString name = "None";
                    QString cp_id = "None";
                    QString normal_state = "None";
                    QString fail_state = "None";
                    int cur_state = 0;
                    this->cur_obj_id = object->get_id();

                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
                            name = db_request_result.value(1).toString();
                            cp_id = db_request_result.value(2).toString();
                            normal_state = db_request_result.value(3).toString();
                            fail_state = db_request_result.value(4).toString();
                            cur_state = db_request_result.value(5).toInt();

                            qDebug() << name << cp_id << normal_state << fail_state << cur_state;
                        }
                    }


                    if (cur_state < (object->get_patterns().size() - 1))
                    {
                        cur_state += 1;
                    }
                    else
                    {
                        cur_state = 0;
                    }
                    update_table_lib(name, cp_id.toInt(),
                                     normal_state.toInt(),
                                     fail_state.toInt(), cur_state, cur_obj_id);
                    updateScene();
                }

                //ebug() << "Новые координаты точки:" << newPoint;
            }
        }
    }
}


void MyView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        qDebug() << event->pos().x() << " " << event->pos().y();
        QPoint point(event->pos().x(), event->pos().y());
        qDebug() << "Начальные координаты точки:" << point;

        for (auto object : scheme_params.objects_vector)
        {
            std::string tp_obj = object->get_type_object();
            // qDebug() << tp_obj;
            if (tp_obj == "Библиотечный объект")
            {
                qDebug() << "Библиотечный объект";
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;

                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));


                //transform.rotate(-1 * object[4].toInt());

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);

                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    qDebug() << "Find it";
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();

                    newWindow->move(event->pos().x() + hor_off, event->pos().y() + ver_off);

                    qDebug() << object->get_id() << "Id";

                    QSqlQuery db_request_result = connection_to_db_with_lib();

                    QString name = "None";
                    QString cp_id = "None";
                    QString normal_state = "None";
                    QString fail_state = "None";
                    QString cur_state = "None";
                    this->cur_obj_id = object->get_id();

                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
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
            }
            else if (tp_obj == "Телеизмерение")
            {
                qDebug() << "Телеизмерение";
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;

                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));


                //transform.rotate(-1 * object[4].toInt());

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);

                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    qDebug() << "Find it";
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();

                    newWindow->move(event->pos().x() + hor_off, event->pos().y() + ver_off);

                    qDebug() << object->get_id() << "Id";

                    QSqlQuery db_request_result = connection_to_db_with_measure();

                    QString name = "None";
                    QString cp_id = "None";
                    QString cur_value = "None";
                    QString min_value = "None";
                    QString max_value = "None";

                    this->cur_obj_id = object->get_id();

                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
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
            }
            else if (tp_obj == "Телеконтроль")
            {
                qDebug() << "Телеконтроль";
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;

                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));


                //transform.rotate(-1 * object[4].toInt());

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);

                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    qDebug() << "Find it";
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();

                    newWindow->move(event->pos().x() + hor_off, event->pos().y() + ver_off);

                    qDebug() << object->get_id() << "Id";

                    QSqlQuery db_request_result = connection_to_db_with_control();

                    QString name = "None";
                    QString cp_id = "None";

                    this->cur_obj_id = object->get_id();

                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
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
            }
            else if (tp_obj == "Телесигнализация")
            {
                qDebug() << "Телесигнализация";
                QPoint original_point = point;
                // Создаем объект преобразования
                QTransform transform;

                transform.translate(-1 * (object->get_x() + object->get_width() / 2),
                                    -1 * (object->get_y() + object->get_height() / 2));


                //transform.rotate(-1 * object[4].toInt());

                // Применяем преобразование к точке
                QPoint newPoint = transform.map(point);

                if (newPoint.x() >= (-1 * object->get_width() / 2) && newPoint.x() <= object->get_width() / 2 &&
                    newPoint.y() >= (-1 * object->get_height() / 2) && newPoint.y() <= object->get_height() / 2)
                {
                    qDebug() << "Find it";
                    transform.reset();


                    int hor_off = 30;
                    int ver_off = -30;

                    newWindow = new QMenu();

                    newWindow->move(event->pos().x() + hor_off, event->pos().y() + ver_off);

                    qDebug() << object->get_id() << "Id";

                    QSqlQuery db_request_result = connection_to_db_with_signal();

                    QString name = "";
                    QString cp_id = "";

                    this->cur_obj_id = object->get_id();

                    while (db_request_result.next())
                    {
                        if (db_request_result.value(0).toInt() == object->get_id())
                        {
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
    qDebug() << "update";
    update_table_lib(this->lineEdit1->text(), this->lineEdit2->text().toInt(), this->lineEdit3->text().toInt(),
                     this->lineEdit4->text().toInt(), this->lineEdit5->text().toInt(), cur_obj_id);
    updateScene();
    newWindow->hide();
}

void MyView::updateTablemes()
{
    qDebug() << "update";
    update_table_mes(this->lineEdit1->text(), this->lineEdit2->text().toInt(), this->lineEdit3->text().toDouble(),
                     this->lineEdit4->text().toDouble(), this->lineEdit5->text().toDouble(), cur_obj_id);
    updateScene();
    newWindow->hide();
}

void MyView::updateTablecontrol()
{
    qDebug() << "update";
    update_table_control(this->lineEdit1->text(), this->lineEdit2->text().toInt(), cur_obj_id);
    updateScene();
    newWindow->hide();
}

void MyView::updateTablesign()
{
    qDebug() << "update";
    update_table_sign(this->lineEdit1->text(), this->lineEdit2->text().toInt(), cur_obj_id);
    updateScene();
    newWindow->hide();
}