#pragma once

#include <QMap>
#include <memory>
#include "Order.h" // Подключаем заголовочный файл с классом Order

typedef QMap<int, std::shared_ptr<Order>> OrderMap;

class OrderRepository {
public:
    OrderRepository() = default;
    ~OrderRepository() = default;

    // Добавить новый приказ
    int add(std::shared_ptr<Order> order);

    // Получить приказ по ID
    std::shared_ptr<Order> get(int id);

    // Удалить приказ
    bool remove(int id);

    // Получить все приказы
    const OrderMap& getAll() const;

private:
    OrderMap repository;
    int currentId = 0; // Для автоматической генерации ID

    int makeNewId();
};