#include "asteroids/include/systems/MovementSystem.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

MovementSystem::MovementSystem(const shared_ptr<GameConfig> config) : _config(config) {
}

void MovementSystem::updateNode(MovementNode& node, const double time) {
    node.position->position.x += node.motion->velocity.x * time;
    node.position->position.y += node.motion->velocity.y * time;

    if (node.position->position.x < 0) {
        node.position->position.x += this->_config->width;
    }
    if (node.position->position.x > this->_config->width) {
        node.position->position.x -= this->_config->width;
    }
    if (node.position->position.y < 0) {
        node.position->position.y += this->_config->height;
    }
    if (node.position->position.y > this->_config->height) {
        node.position->position.y -= this->_config->height;
    }

    node.position->rotation += node.motion->angularVelocity * time;
    if (node.motion->damping > 0) {
        double xdamp = fabs(cos(node.position->rotation) * node.motion->damping * time);
        double ydamp = fabs(sin(node.position->rotation) * node.motion->damping * time);
        if (node.motion->velocity.x > xdamp) {
            node.motion->velocity.x -= xdamp;
        }
        else if (node.motion->velocity.x < -xdamp) {
            node.motion->velocity.x += xdamp;
        }
        else {
            node.motion->velocity.x = 0;
        }

        if (node.motion->velocity.y > ydamp) {
            node.motion->velocity.y -= ydamp;
        }
        else if (node.motion->velocity.y < -ydamp) {
            node.motion->velocity.y += ydamp;
        }
        else {
            node.motion->velocity.y = 0;
        }
    }
}

}
}
}
}
