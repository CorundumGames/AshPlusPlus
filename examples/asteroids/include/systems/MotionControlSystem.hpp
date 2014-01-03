#ifndef MOTIONCONTROLSYSTEM_HPP
#define MOTIONCONTROLSYSTEM_HPP

#include <cmath>

#include <SFML/Window/Keyboard.hpp>

#include "ash/tools/ListIteratingSystem.hpp"

#include "asteroids/include/nodes/MotionControlNode.hpp"

namespace ash {
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
    public:
        MotionControlSystem() {}
        ~MotionControlSystem() {}
    protected:
        void updateNode(MotionControlNode& node, const double time) override {
            if (Keyboard::isKeyPressed(node.controls->left)) {
                node.position->rotation -= node.controls->rotationRate * time;
            }

            if (Keyboard::isKeyPressed(node.controls->right)) {
                node.position->rotation += node.controls->rotationRate * time;
            }

            if (Keyboard::isKeyPressed(node.controls->accelerate)) {
                node.motion->velocity.x += cos(node.position->rotation) * node.controls->accelerationRate * time;
                node.motion->velocity.y += sin(node.position->rotation) * node.controls->accelerationRate * time;
            }
        }
};
}
}
}
}
#endif // MOTIONCONTROLSYSTEM_HPP
