#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>

#pragma once


class MyWidget : public QFrame {
Q_OBJECT
public:
    QVBoxLayout *layout;
    QGraphicsScene *scene;
    QGraphicsView *view;

    MyWidget();

    void draw_new_scheme(const std::string &filepath);

private:
    //void paintEvent(QPaintEvent* event);

};

