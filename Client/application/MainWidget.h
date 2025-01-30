#pragma once

#include "MainView.h"
#include "db_lib/DBManager.h"

#include <QSqlQuery>
#include <parser_lib/src/SchemeFileNS.h>
#include <socket_client/lib/arm_client.h>

class MainWindow;

class MainWidget : public QFrame
{
    Q_OBJECT

public:
    MainWindow *main_window;
    QSqlQuery db_request_result_actual;
    QSqlQuery db_request_result_cp_actual;

    QSqlQuery db_request_result_previous;
    QSqlQuery db_request_result_cp_previous;

    QVBoxLayout* layout;
    MainView* view = nullptr;
    QGraphicsScene* scene;

    explicit MainWidget(MainWindow* _main_window);

    ~MainWidget()
    {
        stopThread();
        delete layout;
        delete view;
        delete scene;
    };

    void draw_new_scheme(const std::string& filepath);

    void updateScene();

    QThread* m_thread = nullptr;
    QTimer* m_timer = nullptr;

    std::ofstream logs_file_; // Файл логов

    void startThread();
    void stopThread();
    void make_bd_objects();

    signals:
        void stopTimerSignal();

    public slots:
        void stopTimerAndDelete();
    void updateDB();
};