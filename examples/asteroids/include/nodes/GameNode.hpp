#ifndef GAMENODE_HPP
#define GAMENODE_HPP

#include <memory>

#include "ash/core/Node.hpp"

#include "asteroids/include/components/GameState.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::components::GameState;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct GameNode : public Node
{
    GameNode() {}
    shared_ptr<GameState> state;
};
}
}
}
}

#endif // GAMENODE_HPP
