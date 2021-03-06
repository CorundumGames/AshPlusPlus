#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "ash/core/Component.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
using ash::core::Component;
struct GameState : public Component
{
    GameState() : lives(3), level(0), points(0) {}
    int lives;
    int level;
    int points;

};
}
}
}
}

#endif // GAMESTATE_HPP
