#pragma once

#include <QFrame>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QMenu>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>


class MyView : public QGraphicsView {
Q_OBJECT
public:
    MyView() = default;

    explicit MyView(QGraphicsScene *parent);

    void mouseDoubleClickEvent(QMouseEvent *event) override;
};