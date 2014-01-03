#ifndef ENTITYCREATOR_HPP
#define ENTITYCREATOR_HPP

#include <memory>

#include "ash/core/Engine.hpp"
#include "ash/core/Entity.hpp"
#include "asteroids/include/components/Asteroid.hpp"
#include "asteroids/include/components/Gun.hpp"
#include "asteroids/include/components/Position.hpp"


namespace net {
namespace richardlord {
namespace asteroids {
using std::shared_ptr;
using ash::core::Engine;
using ash::core::Entity;
using net::richardlord::asteroids::components::Gun;
using net::richardlord::asteroids::components::Position;
using net::richardlord::asteroids::components::Asteroid;
class EntityCreator
{
    public:
        EntityCreator(const shared_ptr<Engine> engine) : _engine(engine) {}

        void destroyEntity(const shared_ptr<Entity> entity);
        shared_ptr<Entity> createGame();
        shared_ptr<Entity> createAsteroid(const double radius, const double x, const double y);
        shared_ptr<Entity> createSpaceship();
        shared_ptr<Entity> createUserBullet(const Gun& gun, const Position& position);
    private:
        shared_ptr<Engine> _engine;
};
}
}
}

#endif // ENTITYCREATOR_HPP
