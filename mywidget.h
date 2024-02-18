#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QFrame>

class MyWidget : public QFrame
{
    Q_OBJECT

private:
    void paintEvent(QPaintEvent *event);
};


#endif // MYWIDGET_H
