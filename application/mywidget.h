#pragma once

#include "myview.h"

#include <QSqlQuery>
#include <parser_lib/src/SchemeFileNS.h>

class MyWidget : public QFrame
{
    Q_OBJECT

public:
    QSqlQuery db_request_result_actual;
    QSqlQuery db_request_result_cp_actual;

    QSqlQuery db_request_result_previous;
    QSqlQuery db_request_result_cp_previous;

    QVBoxLayout* layout;
    MyView* view;
    QGraphicsScene* scene;

    MyWidget();

    ~MyWidget()
    {
        stopThread();
        delete layout;
        delete view;
        delete scene;
    };

    void draw_new_scheme(const std::string& filepath);

    QThread* m_thread = nullptr;
    QTimer* m_timer = nullptr;

    std::ofstream logs_file_; // Файл логов

    void startThread()
    {
        if (m_thread)
        {
            stopThread();
        }

        // logs_file_.open("../logs/db.log");

        // Создаем новый поток
        m_thread = new QThread(this);

        // Создаем таймер и перемещаем его в новый поток
        m_timer = new QTimer();
        m_timer->moveToThread(m_thread);

        // Соединяем сигнал запуска потока с лямбда-функцией, которая запускает таймер
        connect(m_thread, &QThread::started, m_timer, [=]()
        {
            m_timer->start(1000); // Запускаем таймер с интервалом в 1 секунду
        });

        // Соединяем сигнал таймера с нашим слотом updateDB
        connect(m_timer, &QTimer::timeout, this, &MyWidget::updateDB);

        // Соединяем сигнал завершения потока с удалением таймера
        connect(m_thread, &QThread::finished, m_timer, &QTimer::deleteLater);

        // Соединяем сигнал завершения потока с удалением самого потока
        connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);

        // Запускаем поток
        m_thread->start();
    }

    void stopThread()
    {
        if (m_thread)
        {
            m_thread->quit(); // Просим поток завершиться
            m_thread->wait(); // Ждем завершения потока
            delete m_timer; // Удаляем таймер
            delete m_thread;
            m_timer = nullptr;
            m_thread = nullptr;

            // logs_file_.close();
        }
    }

    void make_bd_objects();


public slots:
    void updateDB()
    {
        if (!view->scheme_params.objects_vector.size())
            return;

        db_request_result_previous = db_request_result_actual;
        // db_request_result_cp_previous = db_request_result_cp_actual;

        db_request_result_actual = connection_to_db();
        // db_request_result_cp_actual = connection_to_cp_db();

        // if (db_request_result_actual.size() == db_request_result_previous.size()) {
        //     bool flag = false;
        //     while (db_request_result_actual.next() && db_request_result_previous.next()) {
        //         for (int i = 0; i < db_request_result_actual.record().count(); ++i) {
        //             if (db_request_result_actual.value(i) != db_request_result_previous.value(i)) {
        //                 flag = true;
        //             }
        //         }
        //     }
        //     if (!flag)
        //     {
        //         return;
        //     }
        // }

        std::string help_text;

        FiguresClasses::Primitive* cur_prim;

        while (db_request_result_actual.next())
        {
            if (view->bd_objects.find(db_request_result_actual.value(0).toInt()) != view->bd_objects.end())
            {
                cur_prim = view->bd_objects[db_request_result_actual.value(0).toInt()];
                if (cur_prim->get_type_object() == "Библиотечный объект")
                {
                    cur_prim->set_condition(db_request_result_actual.value(2).toInt());
                }
                else if (cur_prim->get_type_object() == "Телеизмерение" || cur_prim->get_type_object() ==
                    "Телеконтроль" || cur_prim->get_type_object() == "Телесигнализация")
                {
                    cur_prim->set_text(db_request_result_actual.value(3).toString().toStdString());
                }
            }
        }

        // lae::writeLog(logs_file_, "Обновился", true);

        // for (auto object : view->scheme_params.objects_vector)
        // {
        //     if (object->get_type_object() == "Библиотечный объект")
        //     {
        //         while (db_request_result_.next())
        //         {
        //             if (db_request_result_.value(0).toInt() == object->get_id())
        //             {
        //                 object->set_condition(db_request_result_.value(2).toInt());
        //                 while (db_request_result_cp_.next())
        //                 {
        //                     if (db_request_result_cp_.value(0).toInt() == db_request_result_.value(4).toInt())
        //                     {
        //                         help_text = db_request_result_.value(1).toString().toStdString() + " (" +
        //                             db_request_result_cp_.value(1).toString().toStdString() + ")";
        //                         object->set_help_text(help_text);
        //                         break;
        //                     }
        //                 }
        //                 break;
        //             }
        //         }
        //         db_request_result_.seek(0);
        //         db_request_result_cp_.seek(0);
        //     }
        //     else if (object->get_type_object() == "Телеизмерение")
        //     {
        //         while (db_request_result_.next())
        //         {
        //             if (db_request_result_.value(0).toInt() == object->get_id())
        //             {
        //                 object->set_text(db_request_result_.value(3).toString().toStdString());
        //                 while (db_request_result_cp_.next())
        //                 {
        //                     if (db_request_result_cp_.value(0).toInt() == db_request_result_.value(4).toInt())
        //                     {
        //                         std::string cur_value = db_request_result_.value(4).toString().toStdString();
        //                         object->set_text(cur_value);
        //
        //                         help_text = db_request_result_.value(1).toString().toStdString() + " (" +
        //                             db_request_result_cp_.value(1).toString().toStdString() + ")";
        //                         object->set_help_text(help_text);
        //                         break;
        //                     }
        //                 }
        //                 break;
        //             }
        //         }
        //         db_request_result_.seek(0);
        //         db_request_result_cp_.seek(0);
        //     }
        //     else if (object->get_type_object() == "Телеконтроль")
        //     {
        //         while (db_request_result_.next())
        //         {
        //             if (db_request_result_.value(0).toInt() == object->get_id())
        //             {
        //                 object->set_text(db_request_result_.value(3).toString().toStdString());
        //                 while (db_request_result_cp_.next())
        //                 {
        //                     if (db_request_result_cp_.value(0).toInt() == db_request_result_.value(4).toInt())
        //                     {
        //                         help_text = db_request_result_.value(1).toString().toStdString() + " (" +
        //                             db_request_result_cp_.value(1).toString().toStdString() + ")";
        //                         object->set_help_text(help_text);
        //                         break;
        //                     }
        //                 }
        //                 break;
        //             }
        //         }
        //         db_request_result_.seek(0);
        //         db_request_result_cp_.seek(0);
        //     }
        //     else if (object->get_type_object() == "Телесигнализация")
        //     {
        //         while (db_request_result_.next())
        //         {
        //             if (db_request_result_.value(0).toInt() == object->get_id())
        //             {
        //                 object->set_text(db_request_result_.value(3).toString().toStdString());
        //                 while (db_request_result_cp_.next())
        //                 {
        //                     if (db_request_result_cp_.value(0).toInt() == db_request_result_.value(4).toInt())
        //                     {
        //                         help_text = db_request_result_.value(1).toString().toStdString() + " (" +
        //                             db_request_result_cp_.value(1).toString().toStdString() + ")";
        //                         object->set_help_text(help_text);
        //                         break;
        //                     }
        //                 }
        //                 break;
        //             }
        //         }
        //         db_request_result_.seek(0);
        //         db_request_result_cp_.seek(0);
        //     }
        // }


        QPixmap pix(view->scheme_params.width, view->scheme_params.height);
        QColor bgColor = {
            view->scheme_params.bgColor.red, view->scheme_params.bgColor.green, view->scheme_params.bgColor.blue
        };
        pix.fill(bgColor);

        QPainter* painter = new QPainter(&pix);

        Scheme scheme(view->scheme_params);
        scheme.draw_scheme(*painter);
        delete painter;
        scene->clear();
        scene->addPixmap(pix);
    }
};
