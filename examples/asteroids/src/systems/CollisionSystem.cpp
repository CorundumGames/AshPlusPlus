#include "asteroids/include/systems/CollisionSystem.hpp"

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

void net::richardlord::asteroids::systems::CollisionSystem::addToEngine(Engine& engine) {
    *(this->_asteroids) = engine.getNodeList<AsteroidCollisionNode>();
    *(this->_bullets) = engine.getNodeList<BulletCollisionNode>();
    *(this->_spaceships) = engine.getNodeList<SpaceshipCollisionNode>();
}

void net::richardlord::asteroids::systems::CollisionSystem::removeFromEngine(Engine& engine) {
    this->_asteroids = nullptr;
    this->_bullets = nullptr;
    this->_spaceships = nullptr;
}

void net::richardlord::asteroids::systems::CollisionSystem::update(const double time) {
    for (BulletCollisionNode i : *(this->_bullets)) {
        for (AsteroidCollisionNode j : *(this->_asteroids)) {

        }
    }

    for (SpaceshipCollisionNode& i : *(this->_spaceships)) {
        for (AsteroidCollisionNode& j : *(this->_asteroids)) {
        }
    }


    /*
    for (bullet in bullets)
        {
            for (asteroid in asteroids)
            {
                if (Point.distance(asteroid.position.position, bullet.position.position) <= asteroid.collision.radius)
                {
                    creator.destroyEntity(bullet.entity);
                    if (asteroid.collision.radius > 10)
                    {
                        creator.createAsteroid(asteroid.collision.radius - 10, asteroid.position.position.x + Math.random() * 10 - 5, asteroid.position.position.y + Math.random() * 10 - 5);
                        creator.createAsteroid(asteroid.collision.radius - 10, asteroid.position.position.x + Math.random() * 10 - 5, asteroid.position.position.y + Math.random() * 10 - 5);
                    }
                    creator.destroyEntity(asteroid.entity);
                    break;
                }
            }
        }

        for (spaceship in spaceships)
        {
            for (asteroid in asteroids)
            {
                if (Point.distance(asteroid.position.position, spaceship.position.position) <= asteroid.collision.radius + spaceship.collision.radius)
                {
                    spaceship.spaceship.fsm.changeState("destroyed");
                    break;
                }
            }
        }
        */
}
