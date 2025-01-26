#pragma once

#include <iostream>
#include <cinttypes>
#include "QString"

enum actionType {
    switchOn,
    switchOff
};

class Order {
public:
    Order(const QString &_author, const QString &_executor, const actionType _action, const QString &_object,
          const QString &_cpName): author(_author), executor(_executor), action(_action), object(_object),
                                   cpName(_cpName) {
    };

    virtual ~Order() = default;

protected:
    QString author;
    QString executor;
    actionType action;
    QString object;
    QString cpName;

    bool virtual ExecuteOrder();
};
