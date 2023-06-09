#include <thread>
#include <memory>
#include <cerrno>
#include <iostream>
#include <string>
#include <cstring>

#include "Controller.hpp"
#include "../../env.hpp"

using msg_t = std::unique_ptr<char[]>;
using tcpclient_t = networking::TCPClient;

void Controller::listen() {
    while(c->receive(store->getServerMessage(), BUFFER_SIZE)) {
        std::string msg = store->getServerMessage();
        store->uploadChatMessage(msg);
    }

    // Очистка буфера
    memset(store->getServerMessage(), 0, BUFFER_SIZE);
}

Controller::Controller(Storage *store) {
    this->store = store;
    c = new tcpclient_t;

    if(!c->connect(SERVER_ADDRESS, SERVER_PORT)) {
        throw std::strerror(errno);
    }

    std::cout << "Подключен к серверу" << std::endl;

    // Запуск потока, читающего ответы сервера
    thrd = std::thread(&Controller::listen, this);
    // Запуск параллельного потока
    if(thrd.joinable()) {
        thrd.detach();
    }
}

void Controller::speak() {
    // Инициализация пользователя
    std::cout << "Введите имя пользователя: " << std::endl;
    if(!std::cin.getline(store->getUsername(), USERNAME_SIZE)) {
        throw "Username entry error";
    }
    system("clear");

    char* prep = new char[USERNAME_SIZE+BUFFER_SIZE];
    std::string msg;

    while(c->connected()) {
        if(!std::cin.getline(store->getClientMessage(), BUFFER_SIZE)) {
            throw "Message entry error";
        }

        strcat(prep, "[");
        strcat(prep, store->getUsername());
        strcat(prep, "]: ");
        strcat(prep, store->getClientMessage());

        c->send(prep, strlen(prep));
        msg = prep;
        store->uploadChatMessage(msg);

        // Очистка буфера
        memset(store->getClientMessage(), 0, BUFFER_SIZE);
        memset(prep, 0, USERNAME_SIZE+BUFFER_SIZE);
    }

    delete prep;
}

Controller::~Controller() {
    delete c;
}