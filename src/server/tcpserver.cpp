#include <iostream>
#include <sys/socket.h>
#include <string.h>

#include "tcpserver.hpp"

namespace networking {
    TCPServer::TCPServer()
        : server(),
        socket_server(std::make_unique<TCPSocket>()),
        is_running(false)
    {}


    bool TCPServer::start(const unsigned int port) {
        if(!socket_server->open()) {
            return false;
        }

        int opt = 1;
        /*
            setsockopt(socket, level, option_name, option_value, option_len)
            @param {int} socket - дескриптор сокета
            @param {int} level - уровень протокола на уровне библиотеки
            @param {int} option_name - разрешает повторное использование локальных адресов 
            @param option_value - значение параметра
            @param {socketlen_t} option_len - длина параметра
        */
        if(setsockopt(socket_server->getSocket(), SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(int)) < 0) {
            return false;
        }

        bzero(&server, sizeof(sockaddr_in));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(port);

        /*
            bind(socket, address, address_len)
            @param {int} socket - дескриптор сокета
            @param {sockaddr} address - структура sockaddr
            @param {socketlen_t} address_len - размер структуры
        */
        if(bind(socket_server->getSocket(), (struct sockaddr*)&server, sizeof(server)) < 0) {
            return false;
        }

        /*
            listen(socket, backlog)
            @param {int} socket - дескриптор сокета
            @param {int} backlog - ограничитель на кол-во соединений
        */
        if(listen(socket_server->getSocket(), MAX_CLIENTS) < 0) {
            return false;
        }

        is_running = true;
        return true;
    }

    bool TCPServer::stop() {
        is_running = false;
        if(!socket_server->close()) {
            return false;
        }
        return true;
    }

    bool TCPServer::send(const TCPSocket *clientID, char *msg, const int size) {
        int msg_bytes = 0;

        if((msg_bytes = clientID->send(msg, size)) < 0) {
            return false;
        } else if (msg_bytes == 0) {
            return false;
        }

        return true;
    }

    bool TCPServer::receive(const TCPSocket *clientID, char *msg, const int size) {
        // Размер полученного сообщения
        int msg_bytes = 0;

        if((msg_bytes = clientID->receive(msg, size)) < 0) {
            return false;
        } else if (msg_bytes == 0) {
            return false;
        }

        return true;
    }

    TCPSocket* TCPServer::waitForConnect() {
        int socket_client= -1;
        sockaddr_in client;
        socklen_t client_length = sizeof(sockaddr_in);

        /*
           accept(socket, address, address_len);
           @param {int} socket - дескриптор сокета
           @param {sockaddr} address - структура sockaddr
           @param {socketlen_t} address_len - размер структуры
        */
        if((socket_client = accept(socket_server->getSocket(), (struct sockaddr*)&client, (socklen_t*)&client_length)) > 0) {
            std::cout << "Новый клиент подключен" << std::endl;
        }

        return new TCPSocket(socket_client);
    }

    bool TCPServer::running() {
        return is_running;
    }
}