#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include <cmath>
#include <memory>

#include <SFML/System/Vector2.hpp>

#include "ash/tools/ListIteratingSystem.hpp"

#include "asteroids/include/GameConfig.hpp"
#include "asteroids/include/nodes/MovementNode.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {
using std::abs;
using std::sin;
using std::cos;
using std::shared_ptr;

using sf::Vector2;

using ash::tools::ListIteratingSystem;

using net::richardlord::asteroids::GameConfig;
using net::richardlord::asteroids::nodes::MovementNode;

class MovementSystem : public ListIteratingSystem<MovementNode>
{
    public:
        MovementSystem(const shared_ptr<GameConfig> config);
    protected:
        void updateNode(MovementNode& node, const double time) override;
    private:
        shared_ptr<GameConfig> _config;
};
}
}
}
}
#endif // MOVEMENTSYSTEM_HPP
