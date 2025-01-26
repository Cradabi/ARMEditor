#pragma once
#include "Order.h"

class ManualOrder : public Order {
    QString connector;

public:
    ManualOrder(const QString &_author, const QString &_connector, const QString &_executor, const actionType _action,
                const QString &_object,
                const QString &_cpName): Order(_author, _executor, _action, _object, _cpName) {
        connector = _connector;
    };

    bool ExecuteOrder() override;
};
