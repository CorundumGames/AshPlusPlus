#ifndef ASTEROIDS_HPP
#define ASTEROIDS_HPP

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
        Asteroids(const shared_ptr<RenderWindow> window, const int width, const int height);
        void start();
    private:
        void prepare(const int width, const int height);

        shared_ptr<GameConfig> _config;
        shared_ptr<Engine> _engine;
        shared_ptr<ITickProvider> _tick_provider;
        shared_ptr<RenderWindow> _window;
        shared_ptr<EntityCreator> _creator;
};
}
}
}

#endif // ASTEROIDS_HPP
