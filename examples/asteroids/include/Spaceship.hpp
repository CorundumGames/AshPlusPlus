#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "ash/core/Component.hpp"
#include "ash/fsm/EntityStateMachine.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {

class Spaceship : public Component
{
    public:
        Spaceship(const EntityStateMachine& fsm) : fsm(fsm) {}
        EntityStateMachine fsm;
};
}
}
}
}
#endif // SPACESHIP_H
