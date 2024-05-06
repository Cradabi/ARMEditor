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


class MyView : public QGraphicsView {
    Q_OBJECT

public:
    MyView() = default;

    explicit MyView(QGraphicsScene* parent);

    void mouseDoubleClickEvent(QMouseEvent* event) override;

private:
    QVector<QVector<QVariant> > vec;

    int cur_obj_id = 0;

    QLineEdit* lineEdit1;
    QLineEdit* lineEdit2;
    QLineEdit* lineEdit3;
    QLineEdit* lineEdit4;
    QLineEdit* lineEdit5;

    QMenu* newWindow;

private slots:
    void updateTablelib();

    void updateTablemes();

    void updateTablecontrol();

    void updateTablesign();
};
