#ifndef MOVEMENTNODE_HPP
#define MOVEMENTNODE_HPP

#include <memory>

#include "ash/core/Node.hpp"

#include "asteroids/include/components/Motion.hpp"
#include "asteroids/include/components/Position.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::components::Motion;
using net::richardlord::asteroids::components::Position;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct MovementNode : public Node
{
    MovementNode() {}
    shared_ptr<Position> position;
    shared_ptr<Motion> motion;
};
}
}
}
}
#endif // MOVEMENTNODE_HPP
