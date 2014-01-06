#ifndef GUNCONTROLSYSTEM_HPP
#define GUNCONTROLSYSTEM_HPP

#include <SFML/Window/Keyboard.hpp>

#include "asteroids/include/nodes/GunControlNode.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

using sf::Keyboard;

using net::richardlord::asteroids::nodes::GunControlNode;

class GunControlSystem : public ListIteratingSystem<GunControlNode>
{
    public:
        GunControlSystem(const shared_ptr<EntityCreator> creator) : ListIteratingSystem(), _creator(creator) {}
    protected:
        void updateNode(GunControlNode& node, const double time) override {
            node.gun->shooting = Keyboard::isKeyPressed(node.control->trigger());
            node.gun->timeSinceLastShot += time;
            if (node.gun->shooting && node.gun->timeSinceLastShot >= node.gun->minimumShotInterval) {
                this->_creator->createUserBullet(*(node.gun), *(node.position));
                node.gun->timeSinceLastShot = 0;
            }
        }
    private:
        shared_ptr<EntityCreator> _creator;
};
}
}
}
}
#endif // GUNCONTROLSYSTEM_HPP
