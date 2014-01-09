#ifndef GUNCONTROLSYSTEM_HPP
#define GUNCONTROLSYSTEM_HPP

#include <SFML/Window/Keyboard.hpp>

#include "ash/tools/ListIteratingSystem.hpp"

#include "asteroids/include/nodes/GunControlNode.hpp"
#include "asteroids/include/EntityCreator.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

using sf::Keyboard;

using ash::tools::ListIteratingSystem;

using net::richardlord::asteroids::nodes::GunControlNode;
using net::richardlord::asteroids::EntityCreator;

class GunControlSystem : public ListIteratingSystem<GunControlNode>
{
    public:
        GunControlSystem(const shared_ptr<EntityCreator> creator);
    protected:
        void updateNode(GunControlNode& node, const double time) override;
    private:
        shared_ptr<EntityCreator> _creator;
};
}
}
}
}
#endif // GUNCONTROLSYSTEM_HPP
