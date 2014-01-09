#include "asteroids/include/systems/GameManager.hpp"


#include <iostream>

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

GameManager::GameManager(const shared_ptr<EntityCreator> creator, const shared_ptr<GameConfig> config) :
    System(),
    _creator(creator),
    _config(config),
    _game_nodes(),
    _spaceships(),
    _asteroids(),
    _bullets() {
}

void GameManager::addToEngine(const shared_ptr<Engine> engine) {
    this->_game_nodes = *engine->getNodeList<GameNode>();
    this->_spaceships = *engine->getNodeList<SpaceshipNode>();
    this->_asteroids = *engine->getNodeList<AsteroidCollisionNode>();
    this->_bullets = *engine->getNodeList<BulletCollisionNode>();
}

void GameManager::update(const double time) {
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

}
}
}
}
