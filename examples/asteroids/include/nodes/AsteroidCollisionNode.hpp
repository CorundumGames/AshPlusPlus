#ifndef ASTEROIDCOLLISIONNODE_HPP
#define ASTEROIDCOLLISIONNODE_HPP

#include <memory>
#include "ash/core/Node.hpp"
#include "asteroids/include/components/Asteroid.hpp"
#include "asteroids/include/components/Position.hpp"
#include "asteroids/include/components/Collision.hpp"

using std::shared_ptr;

using ash::core::Node;

using net::richardlord::asteroids::components::Asteroid;
using net::richardlord::asteroids::components::Position;
using net::richardlord::asteroids::components::Collision;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct AsteroidCollisionNode : public Node
{
    AsteroidCollisionNode() : Node(), asteroid(nullptr), position(nullptr), collision(nullptr) {}
    virtual ~AsteroidCollisionNode() {}

    void reset() override {
        Node::reset();
        this->asteroid = nullptr;
        this->position = nullptr;
        this->collision = nullptr;
    }

    shared_ptr<Asteroid> asteroid;
    shared_ptr<Position> position;
    shared_ptr<Collision> collision;
};
}
}
}
}

#endif // ASTEROIDCOLLISIONNODE_HPP
