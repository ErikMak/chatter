#include <sys/socket.h>
#include <netinet/in.h>

#include "tcpsocket.hpp"

namespace networking {
    TCPSocket::TCPSocket() {}

    TCPSocket::TCPSocket(int &socket) {
        unix_socket = socket;
    }

    bool TCPSocket::open() {
        /*  
            socket(domain, type, protocol)
            @param {int} domain - домен связи
            @param {int} type - тип связи TCP
            @param {int} protocol - протокол для IP
        */
        if((unix_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            return false;
        }
        return true;
    }

    bool TCPSocket::close() {
        /*  
            shutdown(socket, how)
            @param {int} socket - дескриптор сокета
            @param {int} how - отключает дальнейшие операции отправки и получения.
        */
        if(shutdown(unix_socket, SHUT_RDWR) < 0) {
            return false;
        }
        return true;
    }

    int TCPSocket::send(char* msg, const int size) const {
        /*  
            send(socket, buffer, length, flags)
            @param {int} socket - дескриптор сокета
            @param buffer - буфер, содержащий сообщение
            @param {size_t} length - размер сообщения в байтах
            @param {int} - Флаг завершения записи
        */
        return ::send(unix_socket, msg, size, 0);
    }

    int TCPSocket::receive(char *msg, const int size) const {
        /*
            recv(socket, buffer, length, flags)
            @param {int} socket - дескриптор сокета
            @param buffer - буфер, содержащий сообщение
            @param {size_t} length - размер сообщения в байтах
            @param {int} - Флаг просмотра входящего сообщения
        */
        return recv(unix_socket, msg, size, 0);
    }

    int TCPSocket::getSocket() {
        return unix_socket;
    }
}