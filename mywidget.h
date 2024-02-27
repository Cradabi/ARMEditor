#include <QFrame>

#pragma once

class MyWidget : public QFrame {
Q_OBJECT

private:

    void paintEvent(QPaintEvent* event);

};

