#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

#pragma once


class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView(QGraphicsScene* parent) : QGraphicsView(parent)
    {
    }

    void mouseDoubleClickEvent(QMouseEvent* event);
};

class MyWidget : public QFrame
{
    Q_OBJECT

public:
    QVBoxLayout* layout;
    QGraphicsScene* scene;
    MyView* view;

    MyWidget();

    ~MyWidget()
    {
        delete layout;
        delete scene;
        delete view;
    };

    void draw_new_scheme(const std::string& filepath);
};

