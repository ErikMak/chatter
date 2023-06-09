#ifndef H_STORAGE
#define H_STORAGE

#include <memory>
#include <vector>
#include <string>

#include "Subject.hpp"

using msg_t = std::unique_ptr<char[]>;

class Storage : public Subject {
    private:
        // Буфер сообщения от сервера
        msg_t server_msg;
        // Буфер сообщения от клиента
        msg_t client_msg;
        // Массив сообщений чата
        std::vector<std::string> messages;
        // Имя пользователя
        msg_t username;

        static Storage* instance;
        Storage();
    public:
        static Storage* getInstance();
        // Storage();
        char* getUsername();
        char* getServerMessage();
        char* getClientMessage();
        size_t getUsernameSize();
        size_t getClientMessageSize();
        void uploadChatMessage(const std::string msg);
        std::vector<std::string> getChatMessages();
};

#endif