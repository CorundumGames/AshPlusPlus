#include "asteroids/include/systems/AnimationSystem.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace systems {

AnimationSystem::AnimationSystem() : ListIteratingSystem() {
}

void AnimationSystem::updateNode(AnimationNode& node, const double time) {
    node.animation->animation->animate(time);
}

}
}
}
}
