// OrderWidget.h
#pragma once
#include <QWidget>

class OrderWidget : public QWidget {
    Q_OBJECT

public:
    explicit OrderWidget(qint16 orderId, QWidget *parent = nullptr);
    qint16 getOrderId() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;

    signals:
        void clicked(qint16 orderId);

private:
    qint16 orderId;
};