#ifndef DEATHTHROESSYSTEM_HPP
#define DEATHTHROESSYSTEM_HPP

#include "ash/tools/ListIteratingSystem.hpp"
#include "asteroids/include/nodes/DeathThroesNode.hpp"

namespace ash {
namespace richardlord {
namespace asteroids {
namespace systems {
using ash::tools::ListIteratingSystem;
using net::richardlord::asteroids::nodes::DeathThroesNode;
class DeathThroesSystem : public ListIteratingSystem<DeathThroesNode>
{
    public:
        DeathThroesSystem(const shared_ptr<EntityCreator> creator) :
            ListIteratingSystem<DeathThroesNode>(),
            _creator(creator)
        {}
    protected:
        void updateNode(DeathThroesNode& node, const double time) override {
            node.death->countdown -= time;
            if (node.death->countdown <= 0) {
                this->_creator->destroyEntity(node.entity);
            }
        }
    private:
        shared_ptr<EntityCreator> _creator;
};
}
}
}
}

#endif // DEATHTHROESSYSTEM_HPP
