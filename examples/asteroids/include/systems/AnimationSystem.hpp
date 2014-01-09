#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include <functional>
#include <memory>

#include "ash/tools/ListIteratingSystem.hpp"

#include "asteroids/include/nodes/AnimationNode.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

using std::bind;
using std::mem_fn;
using std::shared_ptr;
using std::function;

using ash::tools::ListIteratingSystem;

using net::richardlord::asteroids::nodes::AnimationNode;

using namespace std::placeholders;

class AnimationSystem : public ListIteratingSystem<AnimationNode>
{
    public:
        AnimationSystem();
    private:
        void updateNode(AnimationNode& node, const double time);
};
}
}
}
}

#endif // ANIMATIONSYSTEM_HPP
