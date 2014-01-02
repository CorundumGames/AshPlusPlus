#ifndef ANIMATIONNODE_HPP
#define ANIMATIONNODE_HPP

#include <memory>

#include "ash/core/Node.hpp"
#include "asteroids/include/components/Animation.hpp"


using std::shared_ptr;

using ash::core::Node;

using net::richardlord::asteroids::components::Animation;

namespace net {
namespace richardlord {
namespace asteroids {
namespace nodes {
struct AnimationNode : public Node
{
    AnimationNode() : Node(), animation(nullptr) {}
    shared_ptr<Animation> animation;
    void reset() override {
        this->animation = nullptr;
    }
};
}
}
}
}
#endif // ANIMATIONNODE_HPP
