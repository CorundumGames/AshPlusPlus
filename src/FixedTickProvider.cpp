#include "FixedTickProvider.h"

ash::tick::FixedTickProvider::~FixedTickProvider()
{
    //dtor
}

void ash::tick::FixedTickProvider::add(const Listener& listener) {
    this->_signal.add(listener);
}

void ash::tick::FixedTickProvider::remove(const Listener& listener) {
    this->_signal.remove(listener);
}

bool ash::tick::FixedTickProvider::playing() const {
    return this->_playing;
}

void ash::tick::FixedTickProvider::start() {
    this->_playing = true;
}

void ash::tick::FixedTickProvider::stop() {
    this->_playing = false;
}

void ash::tick::FixedTickProvider::time_adjustment(const double time_adjustment) {
    this->_time_adjustment = time_adjustment;
}

double ash::tick::FixedTickProvider::time_adjustment() const {
    return this->_time_adjustment;
}

