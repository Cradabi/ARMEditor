#pragma once

#include "myview.h"

#include <QSqlQuery>
#include <parser_lib/src/SchemeFileNS.h>
#include <socket_client/lib/arm_client.h>

class MyWidget : public QFrame
{
    Q_OBJECT

public:
    QSqlQuery db_request_result_actual;
    QSqlQuery db_request_result_cp_actual;

    QSqlQuery db_request_result_previous;
    QSqlQuery db_request_result_cp_previous;

    QVBoxLayout* layout;
    MyView* view = nullptr;
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
        emit updateDB();
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
            m_timer->start(60000); // Запускаем таймер с интервалом в 1 секунду
        });

        // Соединяем сигнал таймера с нашим слотом updateDB
        connect(m_timer, &QTimer::timeout, this, &MyWidget::updateDB);

        // // Соединяем сигнал завершения потока с удалением таймера
        // connect(m_thread, &QThread::finished, m_timer, &QTimer::deleteLater);
        //
        // // Соединяем сигнал завершения потока с удалением самого потока
        // connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);

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

        std::string help_text;

        FiguresClasses::Primitive* cur_prim;

        while (db_request_result_actual.next())
        {
            if (view->bd_objects.find(db_request_result_actual.value(0).toInt()) != view->bd_objects.end())
            {
                cur_prim = view->bd_objects[db_request_result_actual.value(0).toInt()];
                if (cur_prim->get_type_object() == "Библиотечный объект")
                {
                    if(db_request_result_actual.value(2).toInt() >= 0)
                    {
                        cur_prim->set_condition(db_request_result_actual.value(2).toInt());
                    }else
                    {
                        update_table_lib_short(0, cur_prim->get_id());
                        cur_prim->set_condition(0);
                    }
                }
                else if (cur_prim->get_type_object() == "Телеизмерение")
                {
                    cur_prim->set_text(db_request_result_actual.value(3).toString().toStdString());
                }
            }
        }

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
