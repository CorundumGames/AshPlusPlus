#include "ash/core/System.hpp"

namespace ash {
namespace core {

System::System(const int priority) : _priority(priority) {
}

System::System() : System(0) {
}

System::~System() {
    //dtor
}

int System::priority() const {
    return this->_priority;
}

void System::priority(const int priority) {
    this->_priority = priority;
}

bool System::operator==(const System& other) const {
    return this->priority() == other.priority();
}

bool System::operator<(const System& other) const {
    return this->priority() < other.priority();
}

void System::addToEngine(const shared_ptr<Engine> engine) {
}

void System::removeFromEngine(const shared_ptr<Engine> engine) {
}
}
}
