#include "OrdersRepository.h"


int OrderRepository::add(std::shared_ptr<Order> order) {
    int id = makeNewId();
    repository[id] = order;
    return id;
}

std::shared_ptr<Order> OrderRepository::get(int id) {
    if (repository.contains(id)) {
        return repository[id];
    }
    return nullptr;
}

bool OrderRepository::remove(int id) {
    return repository.remove(id) > 0;
}

const OrderMap& OrderRepository::getAll() const {
    return repository;
}

int OrderRepository::makeNewId() {
    return ++currentId;
}