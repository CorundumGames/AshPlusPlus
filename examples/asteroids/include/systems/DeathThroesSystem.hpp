#ifndef DEATHTHROESSYSTEM_HPP
#define DEATHTHROESSYSTEM_HPP

#include "ash/tools/ListIteratingSystem.hpp"
#include "asteroids/include/nodes/DeathThroesNode.hpp"
#include "asteroids/include/EntityCreator.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

using ash::tools::ListIteratingSystem;

using net::richardlord::asteroids::nodes::DeathThroesNode;
using net::richardlord::asteroids::EntityCreator;

class DeathThroesSystem : public ListIteratingSystem<DeathThroesNode>
{
    public:
        DeathThroesSystem(const shared_ptr<EntityCreator> creator);
    protected:
        void updateNode(DeathThroesNode& node, const double time) override;
    private:
        shared_ptr<EntityCreator> _creator;
};
}
}
}
}

#endif // DEATHTHROESSYSTEM_HPP
