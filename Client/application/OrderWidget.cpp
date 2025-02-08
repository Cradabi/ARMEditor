// OrderWidget.cpp
#include "OrderWidget.h"
#include <QMouseEvent>

OrderWidget::OrderWidget(qint16 orderId, QWidget *parent)
    : QWidget(parent), orderId(orderId) {}

qint16 OrderWidget::getOrderId() const {
    return orderId;
}

void OrderWidget::mousePressEvent(QMouseEvent *event) {
    // Вызываем сигнал clicked при нажатии мыши.
    emit clicked(orderId);
    // Передаем событие дальше, если нужно.
    QWidget::mousePressEvent(event);
}