#pragma once

#include "Order.h"

class AutomaticOrder : public Order {
public:
    AutomaticOrder(const QString &_author, const QString &_executor, const actionType _action, const QString &_object,
                   const QString &_cpName): Order(_author, _executor, _action, _object, _cpName) {
    };

    bool ExecuteOrder() override;
};
