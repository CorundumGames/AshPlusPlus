#include "asteroids/include/systems/CollisionSystem.hpp"

#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>

using std::hypot;
using std::rand;
using sf::Vector2;

net::richardlord::asteroids::systems::CollisionSystem::CollisionSystem(EntityCreator& creator) :
    _creator(&creator),
    _asteroids(),
    _bullets(),
    _spaceships()
{
    //ctor
}

net::richardlord::asteroids::systems::CollisionSystem::~CollisionSystem()
{
    //dtor
}

void net::richardlord::asteroids::systems::CollisionSystem::addToEngine(const shared_ptr<Engine> engine) {
    *(this->_asteroids) = engine->getNodeList<AsteroidCollisionNode>();
    *(this->_bullets) = engine->getNodeList<BulletCollisionNode>();
    *(this->_spaceships) = engine->getNodeList<SpaceshipCollisionNode>();
}

void net::richardlord::asteroids::systems::CollisionSystem::removeFromEngine(const shared_ptr<Engine> engine) {
    this->_asteroids = nullptr;
    this->_bullets = nullptr;
    this->_spaceships = nullptr;
}

void net::richardlord::asteroids::systems::CollisionSystem::update(const double time) {
    for (BulletCollisionNode b : *(this->_bullets)) {
        for (AsteroidCollisionNode a : *(this->_asteroids)) {
            Vector2<double> temp = a.position->position - b.position->position;
            if (hypot(temp.x, temp.y <= a.collision->radius)) {
                this->_creator->destroyEntity(a.entity);
                if (a.collision->radius > 10) {
                    this->_creator->createAsteroid(
                        a.collision->radius - 10,
                        a.position->position.x + (rand() / RAND_MAX) * 10 - 5,
                        a.position->position.y + (rand() / RAND_MAX)
                    );
                    this->_creator->createAsteroid(
                        a.collision->radius - 10,
                        a.position->position.x + (rand() / RAND_MAX) * 10 - 5,
                        a.position->position.y + (rand() / RAND_MAX)
                    );
                }
                this->_creator->destroyEntity(a.entity);
                break;
            }
        }
    }

    for (SpaceshipCollisionNode& s : *(this->_spaceships)) {
        for (AsteroidCollisionNode& a : *(this->_asteroids)) {
            Vector2<double> temp = a.position->position - s.position->position;
            if (hypot(temp.x, temp.y <= a.collision->radius + s.collision->radius)) {
                s.spaceship->fsm.changeState("destroyed");
                break;
            }
        }
    }
}
