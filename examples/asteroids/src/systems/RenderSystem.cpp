#include "asteroids/include/systems/RenderSystem.hpp"

#include <iostream>

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

RenderSystem::RenderSystem(const shared_ptr<RenderWindow> window) : _nodes(), _window(window) {
}

void RenderSystem::update(const double time) {
    this->_window->clear();
    for (const RenderNode& node : this->_nodes) {
        this->_window->draw(*(node.display->displayObject));
    }
    this->_window->display();
}

void RenderSystem::addToEngine(const shared_ptr<Engine> engine) {
    this->_nodes = *engine->getNodeList<RenderNode>();
}

}
}
}
}
