#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "ash/core/Component.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
class GameState : public Component
{
    public:
        GameState() : lives(3), level(0), score(0) {};
        int lives;
        int level;
        int points;

};
}
}
}
}

#endif // GAMESTATE_HPP
