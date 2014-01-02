#ifndef ANIMATION_H
#define ANIMATION_H

#include <memory>

#include "ash/core/Component.hpp"
#include "asteroids/include/graphics/IAnimatable.hpp"

using std::shared_ptr;

using net::richardlord::asteroids::graphics::IAnimatable;

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
class Animation : public Component
{
    public:
        Animation(shared_ptr<IAnimatable> animation) : animation(animation) {}
        virtual ~Animation() {}
        shared_ptr<IAnimatable> animation;
};
}
}
}
}
#endif // ANIMATION_H
