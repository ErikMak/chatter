#include <iostream>
#include <cstring>
#include <thread>

#include "../env.hpp"
#include "../server/tcpserver.hpp"
#include "../server/tcpsocket.hpp"
#include "../client/models/TCPClient.hpp"

using tcpserver_t = networking::TCPServer;
using tcpclient_t = networking::TCPClient;
using tcpsocket_t = networking::TCPSocket;

void test(tcpserver_t &s, tcpclient_t &c) {
    tcpsocket_t *clientID;
    while(!c.connected()) {
        std::cout << "1";
        clientID = s.waitForConnect();
    }

    std::cout << "NANA";

    char client_msg[32];
    if(s.receive(clientID, client_msg, BUFFER_SIZE)) {
        std::cout << client_msg;
    }

    // // Сообщение от клиента
    // char client_msg[32];

    // while(s.receive(clientID, client_msg, BUFFER_SIZE)) {
    //     std::cout << client_msg;
    // }
}

// void clientConnection(tcpclient_t &c) {
//     while(!c.connected()) {
//         c.connect(SERVER_ADDRESS, SERVER_PORT);
//         std::cout << "Connect";
//     }
// }

int main() {
    tcpserver_t s;
    tcpclient_t c;

    if(!s.start(SERVER_PORT)) {
        std::cout << "Ошибка запуска сервера\n";
        return 1;
    }

    while(!c.connected()) {
        std::thread thrd_1 = std::thread(test, std::ref(s), std::ref(c));
        if(thrd_1.joinable()) {
            thrd_1.detach();
        }

        if(!c.connect(SERVER_ADDRESS, SERVER_PORT)) {
            std::cout << "Ошибка подключения клиента\n";
            return 1;
        }

    }

    // Исходное сообщение
    char str[32] = "Hello world!";

    if(!c.send(str, strlen(str))) {
        std::cout << "Ошибка отправки сообщения клиентом\n";
        return 1;
    }



// tcpsocket_t *clientID;
//     std::thread thrd = std::thread(test, std::ref(s));

//     if(!c.connect(SERVER_ADDRESS, SERVER_PORT)) {
//         std::cout << "Ошибка подключения клиента\n";
//         return 1;
//     }

//     // Исходное сообщения
//     char str[32] = "Hello world!";

//     if(!c.send(str, strlen(str))) {
//         std::cout << "Ошибка отправки сообщения клиентом\n";
//         return 1;
//     }

//     std::cout << "BEBE";

//     // if(client_msg != str) {
//     //     std::cout << "Некорректно полученные данные\n";
//     //     return 1;
//     // }
//     char client_msg[32];

//     if(!s.send(clientID, client_msg, strlen(client_msg))) {
//         std::cout << "Ошибка отправки сообщения сервером\n";
//         return 1;
//     }

//     // Сообщение от сервера
//     char server_msg[32];
//     if(!c.receive(server_msg, strlen(server_msg))) {
//         std::cout << "Ошибка получения сообщения клиентом\n";
//         return 1;
//     }

//     if(server_msg != str) {
//         std::cout << "Некорректно полученные данные\n";
//         return 1;
//     }

//     if(!c.disconnect()) {
//         std::cout << "Ошибка отключения клиента\n";
//         return 1;
//     }

//     if(!s.stop()) {
//         std::cout << "Ошибка остановки сервера\n";
//         return 1;
//     }

//     std::cout << "BA";
}