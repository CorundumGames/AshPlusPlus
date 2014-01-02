#ifndef BULLET_H
#define BULLET_H

#include "ash/core/Component.hpp"

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
class Bullet : public Component
{
    public:
        explicit Bullet(const double lifetime) : lifeRemaining(lifetime) {}
        double lifeRemaining;
};
}
}
}
}

#endif // BULLET_H
