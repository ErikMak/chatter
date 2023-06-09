#ifndef H_VIEW
#define H_VIEW

#include <memory>

#include "Observer.hpp"
#include "../models/Storage.hpp"

class View : public Observer {
    private:
        Storage *store;
    public:
        View(Storage *store);
        virtual void update();
};

#endif