#ifndef MOTION_H
#define MOTION_H

#include <SFML/System/Vector2.hpp>
#include "ash/core/Component.hpp"

using sf::Vector2;

namespace net {
namespace richardlord {
namespace asteroids {
namespace components {
class Motion : public Component
{
    public:
        Motion(double velocityX, double velocityY, double angularVelocity, double damping) :
            velocity(velocityX, velocityY),
            angularVelocity(angularVelocity),
            damping(damping)
            {}
        Vector2<double> velocity;
        double angularVelocity;
        double damping;
};
}
}
}
}

#endif // MOTION_H
