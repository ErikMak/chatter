#ifndef H_TCPCLIENT
#define H_TCPSERVER

#include <arpa/inet.h>

#include "../../server/tcpsocket.hpp"

namespace networking {
    using tcpsocket_t = std::unique_ptr<TCPSocket>;

    class TCPClient {
        private:
            sockaddr_in server;
            tcpsocket_t socket_client;
            bool is_connected;
        public:
            TCPClient();
            ~TCPClient();
            bool disconnect();
            bool connect(const char *server_addr, const unsigned int port);
            bool receive(char *msg, const int size);
            bool send(char *msg, const int size);
            bool connected();
    };
}

#endif