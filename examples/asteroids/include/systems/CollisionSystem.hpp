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
        CollisionSystem(const shared_ptr<EntityCreator> creator);
        ~CollisionSystem();

        void addToEngine(const shared_ptr<Engine> engine) override;

        void removeFromEngine(const shared_ptr<Engine> engine) override;

        void update(const double time) override;
    private:
        NodeList<AsteroidCollisionNode> _asteroids;
        NodeList<BulletCollisionNode> _bullets;
        NodeList<SpaceshipCollisionNode> _spaceships;
        shared_ptr<EntityCreator> _creator;
};
}
}
}
}

#endif // COLLISIONSYSTEM_HPP
