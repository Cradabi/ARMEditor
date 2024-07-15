#pragma once

#include "myview.h"

#include <QSqlQuery>

class MyWidget : public QFrame {
    Q_OBJECT

public:
    QVBoxLayout* layout;
    MyView* view;
    QGraphicsScene* scene;

    MyWidget();

    ~MyWidget() {
        delete layout;
        delete view;
        delete scene;
    };

    void draw_new_scheme(const std::string& filepath);
};
