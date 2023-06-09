#include <vector>
#include <iostream>
#include <string>

#include "View.hpp"

View::View(Storage *store) {
    this->store = store;

    // Добавляем подписку на представление
    store->addSubscriber(this);
}

void View::update() {
    // Очистка консоли
    system("clear");

    // Отрисовка чата
    std::vector<std::string> messages = store->getChatMessages();
    for(const auto &message : messages) {
        std::cout << message << std::endl;
    }
}