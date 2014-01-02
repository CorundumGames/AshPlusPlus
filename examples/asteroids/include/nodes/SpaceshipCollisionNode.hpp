#ifndef SPACESHIPCOLLISIONNODE_HPP
#define SPACESHIPCOLLISIONNODE_HPP

#include <memory>

#include "ash/core/Node.hpp"

#include "asteroids/include/components/Collision.hpp"
#include "asteroids/include/components/Spaceship.hpp"
#include "asteroids/include/components/Position.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::components::Spaceship;
using net::richardlord::asteroids::components::Position;
using net::richardlord::asteroids::components::Collision;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct SpaceshipCollisionNode : public Node
{
    SpaceshipCollisionNode() {}
    shared_ptr<Spaceship> spaceship;
    shared_ptr<Position> position;
    shared_ptr<Collision> collision;

    void reset() override {
        Node::reset();
        this->spaceship = nullptr;
        this->position = nullptr;
        this->collision = nullptr;
    }
};
}
}
}
}
#endif // SPACESHIPCOLLISIONNODE_HPP
