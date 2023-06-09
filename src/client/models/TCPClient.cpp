#include <sys/socket.h>
#include <string.h>

#include "TCPClient.hpp"

namespace networking {
    TCPClient::TCPClient() 
        : server(),
        socket_client(std::make_unique<TCPSocket>()),
        is_connected(false) 
    {}

    TCPClient::~TCPClient() {
        if(is_connected) {
            disconnect();
        }
    }

    bool TCPClient::connect(const char *server_addr, const unsigned int port) {
        if(!socket_client->open()) {
            return false;
        }

        bzero(&server, sizeof(sockaddr_in));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = inet_addr(server_addr);
        server.sin_port = htons(port);

        /*
            connect(socket, address, address_len)
            @param {int} socket - дескриптор сокета
            @param {sockaddr} address - структура sockaddr
            @param {socketlen_t} address_len - размер структуры
        */
        if(::connect(socket_client->getSocket(), (struct sockaddr*)&server, sizeof(server)) < 0) {
            return false;
        }

        is_connected = true;
        return true;
    }

    bool TCPClient::disconnect() {
        if(!socket_client->close()) {
            return false;
        }

        is_connected = false;
        return true;
    }

    bool TCPClient::receive(char *msg, const int size) {
        // Размер полученного сообщения
        int msg_bytes = 0;

        if((msg_bytes = socket_client->receive(msg, size)) < 0) {
            return false;
        } else if (msg_bytes == 0) {
            is_connected = false;
            return false;
        }

        return true;
    }

    bool TCPClient::send(char *msg, const int size) {
        // Размер отправляемого сообщения
        int msg_bytes = 0;

        if((msg_bytes = socket_client->send(msg, size)) < 0) {
            return false;
        } else if (msg_bytes == 0) {
            is_connected = false;
            return false;
        }

        return true;
    }

    bool TCPClient::connected() {
        return is_connected;
    }
}