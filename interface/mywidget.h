#pragma once

#include "myview.h"

#include <QSqlQuery>

class MyWidget : public QFrame {
    Q_OBJECT

public:
    QVBoxLayout* layout;
    QGraphicsScene* scene;
    MyView* view;

    MyWidget();

    ~MyWidget() {
        delete layout;
        delete scene;
        delete view;
    };

    void draw_new_scheme(const std::string& filepath);
};
