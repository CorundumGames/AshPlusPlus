#ifndef COLLISION_H
#define COLLISION_H

#include "ash/core/Component.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
struct Collision : public Component
{
    Collision(const double radius) : radius(radius) {}
    double radius;
};
}
}
}
}

#endif // COLLISION_H
