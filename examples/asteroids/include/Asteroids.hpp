#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <iostream>
#include <functional>
#include <memory>

#include <SFML/Graphics.hpp>

#include "ash/core/Engine.hpp"
#include "ash/tick/ITickProvider.hpp"
#include "ash/tick/FixedTickProvider.hpp"

#include "asteroids/include/EntityCreator.hpp"
#include "asteroids/include/GameConfig.hpp"
#include "asteroids/include/systems/AnimationSystem.hpp"
#include "asteroids/include/systems/BulletAgeSystem.hpp"
#include "asteroids/include/systems/CollisionSystem.hpp"
#include "asteroids/include/systems/GameManager.hpp"
#include "asteroids/include/systems/GunControlSystem.hpp"
#include "asteroids/include/systems/MotionControlSystem.hpp"
#include "asteroids/include/systems/MovementSystem.hpp"
#include "asteroids/include/systems/RenderSystem.hpp"
#include "asteroids/include/systems/SystemPriorities.hpp"
#include "asteroids/include/systems/AnimationSystem.hpp"
#include "asteroids/include/systems/DeathThroesSystem.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
using std::function;
using std::bind;
using std::shared_ptr;
using std::make_shared;
using namespace std::placeholders;

using sf::RenderWindow;

using ash::tick::ITickProvider;
using ash::tick::FixedTickProvider;

using namespace net::richardlord::asteroids::systems;
using net::richardlord::asteroids::GameConfig;
using net::richardlord::asteroids::EntityCreator;
class Asteroids
{
    public:
        Asteroids(const shared_ptr<RenderWindow> window, const int width, const int height) :
            _window(window),
            _config(make_shared<GameConfig>(width, height)),
            _engine(make_shared<Engine>()),
            _creator(make_shared<EntityCreator>(_engine))
        {
            this->prepare(width, height);
        }
        void start() {
            this->_tick_provider = make_shared<FixedTickProvider>();
            this->_tick_provider->add(bind(&Engine::update, this->_engine.get(), _1));
            this->_tick_provider->start();

        }
    private:
        shared_ptr<GameConfig> _config;
        shared_ptr<Engine> _engine;
        shared_ptr<ITickProvider> _tick_provider;
        shared_ptr<RenderWindow> _window;
        shared_ptr<EntityCreator> _creator;

        void prepare(const int width, const int height) {
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

};
}
}
}

#endif // ASTEROIDS_H
