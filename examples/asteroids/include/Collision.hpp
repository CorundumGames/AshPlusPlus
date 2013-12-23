#ifndef COLLISION_H
#define COLLISION_H

#include "ash/core/Component.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
class Collision : public Component
{
    public:
        explicit Collision(const double radius) : radius(radius);
        double radius;

};
}
}
}
}

#endif // COLLISION_H
