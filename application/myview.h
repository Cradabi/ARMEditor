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
#include "db_lib/db_connection.h"

class MyView : public QGraphicsView
{
    Q_OBJECT

    // friend class UpdateDBThread;

public:
    MyView(QGraphicsView* parent = nullptr) : QGraphicsView(parent)
    {
        setMouseTracking(true);
        // clickTimer = new QTimer(this);
        // connect(clickTimer, &QTimer::timeout, this, &MyView::handleTimeout);
    }


    ~MyView()
    {
        scheme_params.deleteOBJS();
        scheme_params = {};
    }

    explicit MyView(QGraphicsScene* parent);

    // void mouseDoubleClickEvent(QMouseEvent* event) override;

    void mousePressEvent(QMouseEvent* event) override;

    void mouseDoubleClickEvent(QMouseEvent* event) override;

    // void handleSingleClick(QMouseEvent* event);

    void updateScene();

    Scheme::SchemeParams scheme_params;
    std::unordered_map<int, FiguresClasses::Primitive*> bd_objects;

    QGraphicsScene* scene;

private:
    // QTimer* clickTimer;

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
};
