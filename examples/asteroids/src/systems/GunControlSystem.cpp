#include "asteroids/include/systems/GunControlSystem.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {
GunControlSystem::GunControlSystem(const shared_ptr<EntityCreator> creator) :
    ListIteratingSystem(),
    _creator(creator) {
}

void GunControlSystem::updateNode(GunControlNode& node, const double time) {
    node.gun->shooting = Keyboard::isKeyPressed(node.control->trigger());
    node.gun->timeSinceLastShot += time;
    if (node.gun->shooting && node.gun->timeSinceLastShot >= node.gun->minimumShotInterval) {
        this->_creator->createUserBullet(*(node.gun), *(node.position));
        node.gun->timeSinceLastShot = 0;
    }
}
}
}
}
}
