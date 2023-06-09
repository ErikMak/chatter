#include <vector>

#include "Subject.hpp"

void Subject::notify() {
    size_t size = observers.size();
    for(size_t i = 0; i < size; ++i) {
        observers[i]->update();
    }
}

void Subject::addSubscriber(Observer *obs) {
    this->observers.push_back(obs);
}