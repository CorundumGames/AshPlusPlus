#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <SFML/System/Vector2.hpp>

#include "ash/core/System.hpp"

#include "asteroids/include/nodes/GameNode.hpp"
#include "asteroids/include/nodes/SpaceshipNode.hpp"
#include "asteroids/include/nodes/AsteroidCollisionNode.hpp"
#include "asteroids/include/nodes/BulletCollisionNode.hpp"
#include "asteroids/include/GameConfig.hpp"

namespace ash {
namespace richardlord {
namespace asteroids {
namespace systems {
using sf::Vector2;

using ash::core::System;

using net::richardlord::asteroids::GameConfig;
using net::richardlord::asteroids::nodes::GameNode;
using net::richardlord::asteroids::nodes::SpaceshipNode;
using net::richardlord::asteroids::nodes::AsteroidCollisionNode;
using net::richardlord::asteroids::nodes::BulletCollisionNode;

class GameManager : public System
{
    public:
        GameManager(const shared_ptr<EntityCreator> creator, const shared_ptr<GameConfig> config) :
            System(),
            _creator(creator),
            _config(config),
            _game_nodes(),
            _spaceships(),
            _asteroids(),
            _bullets()
        {}
    protected:
        void addToEngine(const shared_ptr<Engine> engine) override {
            this->_game_nodes = engine->getNodeList<GameNode>();
            this->_spaceships = engine->getNodeList<SpaceshipNode>();
            this->_asteroids = engine->getNodeList<AsteroidCollisionNode>();
            this->_bullets = engine->getNodeList<BulletCollisionNode>();
        }

        void update(const double time) override {
            for (const GameNode& node : this->_game_nodes) {
                if (this->_spaceships.empty()) {
                    if (node.state->lives > 0) {
                        // If we haven't yet gotten a game over...
                        Vector2<double> newpos(this->_config->width / 2, this->_config->height / 2);
                        bool ok_to_add_ship = true;

                        for (const AsteroidCollisionNode& asteroid : this->_asteroids) {
                            Vector2<double> temp = asteroid.position->position - newpos;
                            if (hypot(temp.x, temp.y) <= asteroid.collision->radius + 50) {
                                ok_to_add_ship = false;
                                break;
                            }
                        }

                        if (ok_to_add_ship) {
                            this->_creator->createSpaceship();
                            node.state->lives--;
                        }
                    }
                }

                if (this->_asteroids.empty() && this->_bullets.empty() && !this->_spaceships.empty()) {
                    shared_ptr<SpaceshipNode> ship(this->_spaceships.head());
                    node.state->level++;
                    int asteroidcount = node.state->level + 2;
                    for (int i = 0; i < asteroidcount; ++i) {
                        Vector2<double> pos, temp;
                        do {
                            pos.x = (rand() / RAND_MAX) * this->_config->width;
                            pos.y = (rand() / RAND_MAX) * this->_config->height;
                            temp = pos - ship->position->position;
                        } while (hypot(temp.x, temp.y) <= 80);
                        this->_creator->createAsteroid(30, pos.x, pos.y);
                    }
                }
            }
        }

        void removeFromEngine(const shared_ptr<Engine> engine) override {

        }
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
