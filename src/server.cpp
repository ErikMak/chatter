#include <iostream>
#include <cstring>
#include <cerrno>
#include <memory>
#include <thread>
#include <vector>

#include "server/tcpserver.hpp"
#include "server/tcpsocket.hpp"
#include "env.hpp"

using tcpserver_t = networking::TCPServer;
using tcpsocket_t = networking::TCPSocket;

struct Storage {
    std::vector<tcpsocket_t*> clients;
};

void clientsConnectionHandler(tcpserver_t &s, tcpsocket_t *clientID, Storage &sstore) {
    // Буфер сообщений
    std::unique_ptr<char[]> client_msg(new char[BUFFER_SIZE]);

    while(s.receive(clientID, client_msg.get(), BUFFER_SIZE)) {
        // BROADCAST сообщение
        for(auto client : sstore.clients) {
            if(client != clientID) {
                s.send(std::ref(client), client_msg.get(), BUFFER_SIZE);
            }
        }

        // Очистка буфера
        memset(client_msg.get(), 0, BUFFER_SIZE);
    }

    std::cout << "Пользователь вышел" << std::endl;
}

int main() {
    tcpserver_t s;
    Storage sstore;

    try {
        if(!s.start(SERVER_PORT)) {
            throw std::strerror(errno);
        }

        std::cout << "Сервер запущен по порту " << SERVER_PORT << std::endl;

        while(s.running()) {
            tcpsocket_t *clientID = s.waitForConnect();

            // Добавление клиента в массив клиентов
            sstore.clients.push_back(clientID);

            // Создание потока, удерживающего подключение
            std::thread thrd(clientsConnectionHandler, std::ref(s), clientID, std::ref(sstore));
            // Запуск параллельного потока
            if(thrd.joinable()) {
                thrd.detach();
            }
        }

        if(!s.stop()) {
            throw std::strerror(errno);
        }

        std::cout << "Сервер остановлен" << std::endl;
    } catch (const char* msg) {
        std::cout << msg << std::endl;
    }
    return 0;
}