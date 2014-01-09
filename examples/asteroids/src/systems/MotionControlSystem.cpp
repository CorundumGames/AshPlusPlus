#include "asteroids/include/systems/MotionControlSystem.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

void MotionControlSystem::updateNode(MotionControlNode& node, const double time) {
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
}
}
}
}
