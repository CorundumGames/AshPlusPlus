#ifndef GUNCONTROLS_H
#define GUNCONTROLS_H

#include <SFML/Window/Keyboard.hpp>
#include "ash/core/Component.hpp"

using sf::Keyboard;

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
class GunControls : public Component
{
    public:
        GunControls(const Key& trigger) : _trigger(key) {}
        Key trigger() const {
            return this->_trigger;
        }
    private:
        Key _trigger;
};
}
}
}
}

#endif // GUNCONTROLS_H
