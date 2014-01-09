#include "asteroids/include/systems/DeathThroesSystem.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

DeathThroesSystem::DeathThroesSystem(const shared_ptr<EntityCreator> creator) :
    ListIteratingSystem<DeathThroesNode>(),
    _creator(creator)
{}

void DeathThroesSystem::updateNode(DeathThroesNode& node, const double time) {
    node.death->countdown -= time;
    if (node.death->countdown <= 0) {
        this->_creator->destroyEntity(node.entity);
    }
}
}
}
}
}
