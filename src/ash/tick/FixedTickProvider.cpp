#include <thread>

#include "ash/tick/FixedTickProvider.hpp"

using namespace std::this_thread;

ash::tick::FixedTickProvider::FixedTickProvider() : FixedTickProvider(0.0) {}

ash::tick::FixedTickProvider::FixedTickProvider(const double frameTime) :
    _playing(false),
    _signal(),
    _frame_time(int(frameTime * 1000)),
    _time_adjustment(1.0) {}

ash::tick::FixedTickProvider::~FixedTickProvider()
{
    this->stop();
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
    if (this->_playing) return;
    // Don't let more than one thread run this loop at a time
    this->_playing = true;
    while (this->_playing) {
        std::this_thread::sleep_for(this->_frame_time);
        this->dispatch_tick();
    }
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

void ash::tick::FixedTickProvider::dispatch_tick() {
    this->_signal.dispatch(this->_frame_time.count() * this->_time_adjustment);
}
