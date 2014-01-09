#ifndef BULLET_H
#define BULLET_H

#include "ash/core/Component.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {

using ash::core::Component;

struct Bullet : public Component
{
    explicit Bullet(const double lifetime) : lifeRemaining(lifetime) {}
    double lifeRemaining;
};

}
}
}
}

#endif // BULLET_H
