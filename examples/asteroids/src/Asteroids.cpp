#include "asteroids/include/Asteroids.hpp"


namespace net {
namespace richardlord {
namespace asteroids {

Asteroids::Asteroids(const shared_ptr<RenderWindow> window, const int width, const int height) :
    _window(window),
    _config(make_shared<GameConfig>(width, height)),
    _engine(make_shared<Engine>()),
    _creator(make_shared<EntityCreator>(_engine))
{
    this->prepare(width, height);
}

void Asteroids::start() {
    this->_tick_provider = make_shared<FixedTickProvider>();
    this->_tick_provider->add(bind(&Engine::update, this->_engine.get(), _1));
    this->_tick_provider->start();
}

void Asteroids::prepare(const int width, const int height) {
    this->_engine->addSystem(make_shared<GameManager>(this->_creator, this->_config), SystemPriorities::PRE_UPDATE);
    this->_engine->addSystem(make_shared<MotionControlSystem>(), SystemPriorities::UPDATE);
    this->_engine->addSystem(make_shared<GunControlSystem>(this->_creator), SystemPriorities::UPDATE);
    this->_engine->addSystem(make_shared<BulletAgeSystem>(this->_creator), SystemPriorities::UPDATE);
    this->_engine->addSystem(make_shared<DeathThroesSystem>(this->_creator), SystemPriorities::UPDATE);
    this->_engine->addSystem(make_shared<MovementSystem>(this->_config), SystemPriorities::MOVE);
    this->_engine->addSystem(make_shared<CollisionSystem>(this->_creator), SystemPriorities::RESOLVE_COLLISIONS);
    this->_engine->addSystem(make_shared<AnimationSystem>(), SystemPriorities::ANIMATE);
    this->_engine->addSystem(make_shared<RenderSystem>(this->_window), SystemPriorities::RENDER);

    this->_creator->createGame();
}

}
}
}
