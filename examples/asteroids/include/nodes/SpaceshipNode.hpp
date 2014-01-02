#ifndef SPACESHIPNODE_HPP
#define SPACESHIPNODE_HPP

#include <memory>

#include "ash/core/Node.hpp"

#include "asteroids/include/components/Spaceship.hpp"
#include "asteroids/include/components/Position.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::components::Spaceship;
using net::richardlord::asteroids::components::Position;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct SpaceshipNode : public Node
{
    SpaceshipNode() {}
    shared_ptr<Spaceship> spaceship;
    shared_ptr<Position> position;
};
}
}
}
}

#endif // SPACESHIPNODE_HPP
