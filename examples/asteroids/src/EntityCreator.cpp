#include "EntityCreator.hpp"

#include "ash/tools/ComponentPool.hpp"

void net::richardlord::asteroids::EntityCreator::destroyEntity(const shared_ptr<Entity> entity) {
    this->_engine->removeEntity(entity);
    if (entity->has<Asteroid>()) {
        ash::tools::ComponentPool<Asteroid>::dispose(entity->get<Asteroid>());
    }
}

shared_ptr<Entity> net::richardlord::asteroids::EntityCreator::createGame() {
}
shared_ptr<Entity> net::richardlord::asteroids::EntityCreator::createAsteroid(
    const double radius, const double x, const double y) {

}
shared_ptr<Entity> net::richardlord::asteroids::EntityCreator::createSpaceship() {
}

shared_ptr<Entity> net::richardlord::asteroids::EntityCreator::createUserBullet(
    const Gun& gun, const Position& position) {

}
