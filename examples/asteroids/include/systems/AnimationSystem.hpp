#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include <functional>
#include <memory>

#include "ash/tools/ListIteratingSystem.hpp"

#include "asteroids/include/nodes/AnimationNode.hpp"

using std::bind;
using std::mem_fn;
using std::shared_ptr;
using std::function;

using ash::tools::ListIteratingSystem;

using net::richardlord::asteroids::nodes::AnimationNode;

using namespace std::placeholders;

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {
class AnimationSystem : public ListIteratingSystem<AnimationNode>
{
    public:
        AnimationSystem() : ListIteratingSystem() {}
    private:
        void updateNode(AnimationNode& node, const double time) {
            node.animation->animation->animate(time);
        }
};
}
}
}
}

#endif // ANIMATIONSYSTEM_HPP
