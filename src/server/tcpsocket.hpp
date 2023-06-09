#ifndef H_TCPSOCKET
#define H_TCPSOCKET

#include <memory>

namespace networking {
    class TCPSocket {
        private:
            int unix_socket; // Дескриптор сокета
        public:
            TCPSocket();
            TCPSocket(int &socket);
            bool open();
            bool close();
            int send(char* msg, const int size) const;
            int receive(char* msg, const int size) const;
            int getSocket();
    };
}

#endif