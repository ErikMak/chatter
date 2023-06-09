#include <memory>
#include <cstring>
#include <vector>
#include <string>

#include "Storage.hpp"
#include "../../env.hpp"

using msg_t = std::unique_ptr<char[]>;

Storage* Storage::instance = 0;

Storage* Storage::getInstance() {
    if(instance == 0) {
        instance = new Storage();
    }

    return instance;
}

Storage::Storage() {
    client_msg = std::make_unique<char[]>(BUFFER_SIZE);
    server_msg = std::make_unique<char[]>(BUFFER_SIZE);
    username = std::make_unique<char[]>(USERNAME_SIZE);
}

char* Storage::getClientMessage() {
    return client_msg.get();
}

size_t Storage::getClientMessageSize() {
    return strlen(client_msg.get());
}

size_t Storage::getUsernameSize() {
    return strlen(username.get());
}

char* Storage::getServerMessage() {
    return server_msg.get();
}

char* Storage::getUsername() {
    return username.get();
}

std::vector<std::string> Storage::getChatMessages() {
    return messages;
}

void Storage::uploadChatMessage(const std::string msg) {
    messages.push_back(msg);

    notify();
}