#ifndef BULLETAGENODE_HPP
#define BULLETAGENODE_HPP

#include <memory>

#include "ash/core/Node.hpp"
#include "asteroids/include/components/Bullet.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::components::Bullet;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct BulletAgeNode : public Node
{
    BulletAgeNode() : Node(), bullet(nullptr) {}
    shared_ptr<Bullet> bullet;

    void reset() override {
        Node::reset();
        this->bullet = nullptr;
    }
};
}
}
}
}

#endif // BULLETAGENODE_HPP
