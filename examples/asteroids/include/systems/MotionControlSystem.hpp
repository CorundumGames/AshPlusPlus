#ifndef MOTIONCONTROLSYSTEM_HPP
#define MOTIONCONTROLSYSTEM_HPP

#include <cmath>

#include <SFML/Window/Keyboard.hpp>

#include "ash/tools/ListIteratingSystem.hpp"

#include "asteroids/include/nodes/MotionControlNode.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

using std::sin;
using std::cos;

using sf::Keyboard;

using ash::tools::ListIteratingSystem;

using net::richardlord::asteroids::nodes::MotionControlNode;

class MotionControlSystem : public ListIteratingSystem<MotionControlNode>
{
    protected:
        void updateNode(MotionControlNode& node, const double time) override;
};
}
}
}
}
#endif // MOTIONCONTROLSYSTEM_HPP
