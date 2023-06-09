#ifndef H_CONTROLLER
#define H_CONTROLLER

#include <thread>
#include <memory>

#include "../models/Storage.hpp"
#include "../models/TCPClient.hpp"

using msg_t = std::unique_ptr<char[]>;
using tcpclient_t = networking::TCPClient;

class Controller {
    private:
        Storage *store;
        tcpclient_t *c;
        std::thread thrd;
    public: 
        void listen();
        Controller(Storage *store);
        void speak();
        ~Controller();
};

#endif