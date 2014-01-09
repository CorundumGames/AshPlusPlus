#ifndef MOTION_HPP
#define MOTION_HPP

#include <SFML/System/Vector2.hpp>
#include "ash/core/Component.hpp"


namespace net {
namespace richardlord {
namespace asteroids {
namespace components {

using sf::Vector2;

using ash::core::Component;

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

#endif // MOTION_HPP
