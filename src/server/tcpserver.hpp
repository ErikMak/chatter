#ifndef H_TCPSERVER
#define H_TCPSERVER

#include <memory>
#include <arpa/inet.h>

#include "tcpsocket.hpp"

namespace networking {
    using tcpsocket_t = std::unique_ptr<TCPSocket>;

    class TCPServer {
        private:
            const unsigned int MAX_CLIENTS = 1024;
            sockaddr_in server; // Структура, описывающая сокет
            tcpsocket_t socket_server;
            bool is_running;     // Статус работы сервера
        public:
            TCPServer();
            bool start(const unsigned int port);
            bool stop();
            bool send(const TCPSocket *clientID, char *msg, const int size);
            bool receive(const TCPSocket *clientID, char *msg, const int size);
            TCPSocket* waitForConnect();
            bool running();
    };
}

#endif