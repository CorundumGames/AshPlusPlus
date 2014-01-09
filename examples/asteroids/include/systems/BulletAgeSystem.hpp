#ifndef BULLETAGESYSTEM_HPP
#define BULLETAGESYSTEM_HPP

#include <memory>

#include "ash/tools/ListIteratingSystem.hpp"

#include "asteroids/include/nodes/BulletAgeNode.hpp"
#include "asteroids/include/EntityCreator.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

using std::shared_ptr;

using ash::tools::ListIteratingSystem;

using net::richardlord::asteroids::EntityCreator;
using net::richardlord::asteroids::nodes::BulletAgeNode;

class BulletAgeSystem : public ListIteratingSystem<BulletAgeNode>
{
    public:
        BulletAgeSystem(const shared_ptr<EntityCreator> creator);
    private:
        void updateNode(BulletAgeNode& node, const double time) override;

        shared_ptr<EntityCreator> _creator;
};

}
}
}
}

#endif // BULLETAGESYSTEM_HPP
