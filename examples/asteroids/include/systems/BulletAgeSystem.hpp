#ifndef BULLETAGESYSTEM_HPP
#define BULLETAGESYSTEM_HPP

#include <memory>

#include "ash/tools/ListIteratingSystem.hpp"

#include "asteroids/include/nodes/BulletAgeNode.hpp"
#include "asteroids/include/EntityCreator.hpp"

using std::shared_ptr;

using ash::tools::ListIteratingSystem;

using net::richardlord::asteroids::EntityCreator;
using net::richardlord::asteroids::nodes::BulletAgeNode;

class BulletAgeSystem : public ListIteratingSystem<BulletAgeNode>
{
    public:
        BulletAgeSystem(EntityCreator& creator) : ListIteratingSystem(), _creator(&creator) {}
        virtual ~BulletAgeSystem() {}
    private:
        shared_ptr<EntityCreator> _creator;

        void updateNode(BulletAgeNode& node, const double time) override {
            node.bullet->lifeRemaining -= time;
            if (node.bullet->lifeRemaining <= 0.0) {
                // If this bullet should disappear...
                this->_creator->destroyEntity(*(node.entity));
            }
        }
};

#endif // BULLETAGESYSTEM_HPP
