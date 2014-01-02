#ifndef BULLETCOLLISIONNODE_HPP
#define BULLETCOLLISIONNODE_HPP

#include <memory>

#include "ash/core/Node.hpp"

#include "asteroids/include/components/Bullet.hpp"
#include "asteroids/include/components/Collision.hpp"
#include "asteroids/include/components/Position.hpp"

using net::richardlord::asteroids::components::Bullet;
using net::richardlord::asteroids::components::Collision;
using net::richardlord::asteroids::components::Position;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct BulletCollisionNode : public Node
{
    BulletCollisionNode() {}
    shared_ptr<Bullet> bullet;
    shared_ptr<Collision> collision;
    shared_ptr<Position> position;
};
}
}
}
}
#endif // BULLETCOLLISIONNODE_HPP
