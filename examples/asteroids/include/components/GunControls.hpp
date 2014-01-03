#ifndef GUNCONTROLS_H
#define GUNCONTROLS_H

#include <SFML/Window/Keyboard.hpp>
#include "ash/core/Component.hpp"


namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
using sf::Keyboard;
typedef sf::Keyboard::Key Key;
class GunControls : public Component
{
    public:
        GunControls(const Key& trigger) : _trigger(trigger) {}
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
