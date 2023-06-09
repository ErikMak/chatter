#ifndef H_SUBJECT
#define H_SUBJECT

#include <vector>
#include <memory>

#include "../views/Observer.hpp"

class Subject {
    private:
        std::vector<class Observer*> observers;
    protected:
        void notify();
    public:
        void addSubscriber(Observer *obs);
        void deleteSubscriber(Observer *obs);
};

#endif