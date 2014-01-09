#include "asteroids/include/systems/BulletAgeSystem.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

BulletAgeSystem::BulletAgeSystem(const shared_ptr<EntityCreator> creator) :
    ListIteratingSystem(),
    _creator(creator) {
}

void BulletAgeSystem::updateNode(BulletAgeNode& node, const double time) {
    node.bullet->lifeRemaining -= time;
    if (node.bullet->lifeRemaining <= 0.0) {
        // If this bullet should disappear...
        this->_creator->destroyEntity(node.entity);
    }
}

}
}
}
}
