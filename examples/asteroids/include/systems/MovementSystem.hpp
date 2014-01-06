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
        MovementSystem(const shared_ptr<GameConfig> config) : _config(config) {}
    protected:
        void updateNode(MovementNode& node, const double time) override {
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
    private:
        shared_ptr<GameConfig> _config;
};
}
}
}
}
#endif // MOVEMENTSYSTEM_HPP
