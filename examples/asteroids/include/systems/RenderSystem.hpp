#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "ash/core/NodeList.hpp"
#include "ash/core/System.hpp"

#include "asteroids/include/nodes/RenderNode.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
using std::shared_ptr;
using sf::RenderWindow;

using ash::core::System;
using ash::core::NodeList;

using net::richardlord::asteroids::nodes::RenderNode;

class RenderSystem : public System
{
    public:
        RenderSystem(const shared_ptr<RenderWindow> window) : _nodes(), _window(window) {}
        ~RenderSystem() {}

        void update(const double time) override {
            for (const RenderNode& node : this->_nodes) {
                this->_window->draw(*(node.display->displayObject));
            }
        }



    protected:
        void addToEngine(const shared_ptr<Engine> engine) override {
            this->_nodes = engine->getNodeList<RenderNode>();
        }
    private:
        NodeList<RenderNode> _nodes;
        shared_ptr<RenderWindow> _window;
};
}
}
}
}
#endif // RENDERSYSTEM_HPP
