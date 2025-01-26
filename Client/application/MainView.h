#pragma once

#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QScrollBar>
#include <QDebug>
#include <QMenu>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTimer>
#include <unordered_map>

#include "primitives_lib/SchemeClass.h"
#include "socket_client/lib/arm_client.h"
#include "db_lib/db_connection.h"

class MainWindow;

class MainView : public QGraphicsView
{
    Q_OBJECT

    // friend class UpdateDBThread;

public:
    MainView(QGraphicsView* parent = nullptr) : QGraphicsView(parent)
    {
        setMouseTracking(true);
        // clickTimer = new QTimer(this);
        // connect(clickTimer, &QTimer::timeout, this, &MyView::handleTimeout);
    }


    ~MainView()
    {

        qDebug() << "myWiev удален";

        // Завершаем поток и освобождаем ресурсы
        clientThread->quit();
        clientThread->wait();
        delete clientWorker;
        delete clientThread;


        scheme_params.deleteOBJS();
        scheme_params = {};
    }

    explicit MainView(QGraphicsScene* parent, MainWindow *_main_window);

    // void mouseDoubleClickEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseDoubleClickEvent(QMouseEvent* event) override;

    // void handleSingleClick(QMouseEvent* event);

    void updateScene();

    Scheme::SchemeParams scheme_params;
    std::unordered_map<int, FiguresClasses::Primitive*> bd_objects;

    QGraphicsScene* scene;

private:

    MainWindow *main_window;
    // QTimer* clickTimer;

    QString messageStatus;

    QPoint lastClickPos;

    // QMouseEvent* lastEvent;

    QVector<QVector<QVariant>> vec;

    int cur_obj_id = 0;

    QLineEdit* lineEdit1;
    QLineEdit* lineEdit2;
    QLineEdit* lineEdit3;
    QLineEdit* lineEdit4;
    QLineEdit* lineEdit5;

    QMenu* newWindow;

    void showOrderDialog(QPoint& point);

private slots:

    // void handleTimeout()
    // {
    //     clickTimer->stop();
    //     handleSingleClick();
    // }

    void updateTablelib();

    void updateTablemes();

    void updateTablecontrol();

    void updateTablesign();

public:

    void startClient(const QString &host, quint16 port);
    void sendMessageToServer(const QString &action, const QString &object);
    void ReadMessageReceivedtest(const QString &message);

    signals:
        void sendCommannd(const QString &action, const QString &object);
        void onMessageReceived(const QString &message);

    private slots:

    void onErrorOccurred(const QString &error);

private:

    QString getUserLogin(const QString &filePath);

    QThread *clientThread;
    arm_client *clientWorker;
};
