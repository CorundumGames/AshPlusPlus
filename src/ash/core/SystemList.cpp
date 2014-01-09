#include "ash/core/SystemList.hpp"

namespace ash {
namespace core {

SystemList::SystemList() : _systems() {
}

SystemList::~SystemList() {
}

void SystemList::add(const shared_ptr<System> system) {
    this->_systems.insert(system);
}

void SystemList::remove(const shared_ptr<System> system) {
    this->_systems.erase(system);
}

void SystemList::removeAll() {
    this->_systems.clear();
}

auto SystemList::begin() -> decltype(SystemList::_systems.begin()) {
    return this->_systems.begin();
}

auto SystemList::end() -> decltype(SystemList::_systems.begin()) {
    return this->_systems.end();
}

}
}
