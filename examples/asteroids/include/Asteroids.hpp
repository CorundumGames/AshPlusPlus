#ifndef ASTEROIDS_H
#define ASTEROIDS_H

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
using std::shared_ptr;
using std::make_shared;

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
            _config(make_shared<GameConfig>()),
            _engine(make_shared<Engine>()),
            _creator(make_shared<EntityCreator>(_engine))
        {
            this->prepare(width, height);
        }
        void start() {
            /*
            tickProvider = new FrameTickProvider( container );
            tickProvider.add(engine.update);
            tickProvider.start();
            */
            this->_tick_provider = make_shared<FixedTickProvider>();

        }
    private:
        shared_ptr<GameConfig> _config;
        shared_ptr<Engine> _engine;
        shared_ptr<ITickProvider> _tick_provider;
        shared_ptr<RenderWindow> _window;
        shared_ptr<EntityCreator> _creator;

        void prepare(const int width, const int height) {

            /*
            engine = new Engine();
            creator = new EntityCreator( engine );
            keyPoll = new KeyPoll( container.stage );
            config = new GameConfig();
            config.width = width;
            config.height = height;

            engine.addSystem(new GameManager( creator, config ), SystemPriorities.preUpdate);
            engine.addSystem(new MotionControlSystem( keyPoll ), SystemPriorities.update);
            engine.addSystem(new GunControlSystem( keyPoll, creator ), SystemPriorities.update);
            engine.addSystem(new BulletAgeSystem( creator ), SystemPriorities.update);
            engine.addSystem(new DeathThroesSystem( creator ), SystemPriorities.update);
            engine.addSystem(new MovementSystem( config ), SystemPriorities.move);
            engine.addSystem(new CollisionSystem( creator ), SystemPriorities.resolveCollisions);
            engine.addSystem(new AnimationSystem(), SystemPriorities.animate);
            engine.addSystem(new RenderSystem( container ), SystemPriorities.render);

            creator.createGame();
            */
        }

};
}
}
}

#endif // ASTEROIDS_H
