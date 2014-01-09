#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/System/Vector2.hpp>

#include "ash/core/NodeList.hpp"
#include "ash/core/System.hpp"

#include "asteroids/include/nodes/GameNode.hpp"
#include "asteroids/include/nodes/SpaceshipNode.hpp"
#include "asteroids/include/nodes/AsteroidCollisionNode.hpp"
#include "asteroids/include/nodes/BulletCollisionNode.hpp"
#include "asteroids/include/GameConfig.hpp"
#include "asteroids/include/EntityCreator.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {
using sf::Vector2;

using ash::core::NodeList;
using ash::core::System;

using net::richardlord::asteroids::EntityCreator;
using net::richardlord::asteroids::GameConfig;
using net::richardlord::asteroids::nodes::GameNode;
using net::richardlord::asteroids::nodes::SpaceshipNode;
using net::richardlord::asteroids::nodes::AsteroidCollisionNode;
using net::richardlord::asteroids::nodes::BulletCollisionNode;

class GameManager : public System
{
    public:
        GameManager(const shared_ptr<EntityCreator> creator, const shared_ptr<GameConfig> config);
    protected:
        void addToEngine(const shared_ptr<Engine> engine) override;

        void update(const double time) override;
    private:
        shared_ptr<GameConfig> _config;
        shared_ptr<EntityCreator> _creator;
        NodeList<GameNode> _game_nodes;
        NodeList<SpaceshipNode> _spaceships;
        NodeList<AsteroidCollisionNode> _asteroids;
        NodeList<BulletCollisionNode> _bullets;
};
}
}
}
}
#endif // GAMEMANAGER_HPP
