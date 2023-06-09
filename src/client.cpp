#include <memory>
#include <iostream>

#include "client/controllers/Controller.hpp"
#include "client/views/View.hpp"
#include "client/models/Storage.hpp"

int main() {
    try {
        // МОДЕЛИ
        Storage *storage = Storage::getInstance();
        // ПРЕДСТАВЛЕНИЕ
        std::unique_ptr<View> view = std::make_unique<View>(storage);
        // КОНТРОЛЛЕР
        std::unique_ptr<Controller> controller = std::make_unique<Controller>(storage);
        controller->speak();
    } catch(const char* msg) {
        std::cout << msg << std::endl;
    }
    return 0;
}