#ifndef COLLISIONSYSTEM_HPP
#define COLLISIONSYSTEM_HPP

#include <memory>

#include "ash/core/Engine.hpp"
#include "ash/core/System.hpp"
#include "ash/core/NodeList.hpp"

#include "asteroids/include/EntityCreator.hpp"
#include "asteroids/include/nodes/AsteroidCollisionNode.hpp"
#include "asteroids/include/nodes/BulletCollisionNode.hpp"
#include "asteroids/include/nodes/SpaceshipCollisionNode.hpp"

using std::shared_ptr;

using ash::core::System;
using ash::core::Engine;
using ash::core::NodeList;

using net::richardlord::asteroids::EntityCreator;
using net::richardlord::asteroids::nodes::AsteroidCollisionNode;
using net::richardlord::asteroids::nodes::BulletCollisionNode;
using net::richardlord::asteroids::nodes::SpaceshipCollisionNode;

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {
class CollisionSystem : public System
{
    public:
        CollisionSystem(EntityCreator& creator);
        ~CollisionSystem();

        void addToEngine(Engine& engine) override;

        void removeFromEngine(Engine& engine) override;

        void update (const double time) override;

    private:
        shared_ptr<NodeList<AsteroidCollisionNode>> _asteroids;
        shared_ptr<NodeList<BulletCollisionNode>> _bullets;
        shared_ptr<NodeList<SpaceshipCollisionNode>> _spaceships;
        shared_ptr<EntityCreator> _creator;
};
}
}
}
}

#endif // COLLISIONSYSTEM_HPP
